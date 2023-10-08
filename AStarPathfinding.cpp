#include"AStarPathfinding.h"


bool notInVector(const vector<pair<int,int>>& vec, const int& x, const int& y) {
	for(const pair<int,int>& element : vec)
		if (element.first == x && element.second == y)
			return false;
	return true;
}


AStarPathfinding::AStarPathfinding() {

	//有可能不是在这里生成
	excelTool = new ExcelTool();
	data = excelTool->data;
	map = data->map;

	start = new MapCell();
	end = new MapCell();

}

AStarPathfinding::~AStarPathfinding()
{
	//delete excelTool;
	//delete start;
	//delete end;
}


void AStarPathfinding::readMap()
{
	excelTool->setMapSheet("map Store1");

	map->max_width = excelTool->getSheetCol();
	map->max_height = excelTool->getSheetRow();

	for (int i = 1; i <= map->max_height; i++) {
		vector<MapCell> line;

		for (int j = 1; j <= map->max_width; j++) {

			MapCell c = getMapCellFromExcel(i, j);
			line.push_back(c);

			if(c.type == CellType::CELL_ENTRANCE)
				map->entranceArea.push_back(c);
			else if(c.type == CellType::CELL_EXIT)
				map->exitArea.push_back(c);
		}
		map->mapCells.push_back(line);
	}


	//寻找货架，并将货架和取货口绑定起来
	int sn = 1;
	vector<pair<int,int>>bannedList;
	for (int i = 0; i < map->max_height; i++)
		for (int j = 0; j < map->max_width; j++) {
			if (map->mapCells[i][j].type == CellType::CELL_SHELF && notInVector(bannedList, i+1,j+1)) {
				//只有不在bannedList中的才能探货架区域

				Shelf sf;
				sf.sn = sn;
				sn++;
				getShelfArea(map->mapCells[i][j], &sf);

				//在知道了shelf的area之后，沿着area的周围查找取货口
				for (int k = 0; k < sf.area.size(); k++) {
					int x = sf.area[k].x;
					int y = sf.area[k].y;
					if (x + 1 <= map->max_height && map->mapCells[x][y - 1].type == CellType::CELL_FETCH)
						sf.fetchList.push_back(map->mapCells[x][y - 1]);
					if (x - 1 >= 1 && map->mapCells[x - 2][y - 1].type == CellType::CELL_FETCH)
						sf.fetchList.push_back(map->mapCells[x - 2][y - 1]);
					if (y - 1 >= 1 && map->mapCells[x - 1][y - 2].type == CellType::CELL_FETCH)
						sf.fetchList.push_back(map->mapCells[x - 1][y - 2]);
					if (y + 1 <= map->max_width && map->mapCells[x - 1][y].type == CellType::CELL_FETCH)
						sf.fetchList.push_back(map->mapCells[x - 1][y]);

					bannedList.push_back(std::make_pair(x,y));
				}

				map->shelfList.push_back(sf);

			}
		}

	bannedList.clear();
}

void AStarPathfinding::getShelfArea(MapCell cur, Shelf* sf)
{
	//往右和下方查找属于同一个shelf的格子
	if (cur.x < map->max_height && map->mapCells[cur.x][cur.y - 1].type == CellType::CELL_SHELF)
		getShelfArea(map->mapCells[cur.x][cur.y - 1], sf);
	if (cur.y < map->max_width && map->mapCells[cur.x - 1][cur.y].type == CellType::CELL_SHELF)
		getShelfArea(map->mapCells[cur.x - 1][cur.y], sf);
	sf->area.push_back(cur);
}

vector<MapCell> AStarPathfinding::getPath(int startX, int startY, int endX, int endY) {
	
	vector<MapCell> vec;
	
	{
	QMutexLocker locker(&getPathMutex);

	start->x = startX;
	start->y = startY;
	end->x = endX;
	end->y = endY;
	end->F = 1;
	end->G = 1;
	curMapCell = start;


	while (!(curMapCell->x == end->x && curMapCell->y == end->y)) {

		getAround();
		moveToMinMapCell();
	}

	
	while (curMapCell->x != start->x || curMapCell->y != start->y) {
		vec.push_back(*curMapCell);
		curMapCell = curMapCell->parent;
	}

	vec.push_back(*curMapCell);
	std::reverse(vec.begin(), vec.end());

	resetMap();
	}

	return vec;
}


//把父节点以及寻路辅助数组给清了
void AStarPathfinding::resetMap()
{
	//估计在这里要mutex格子?
	for (int i = 0; i < openList.size(); i++) {
		map->mapCells[openList[i].first - 1][openList[i].second - 1].clear();
		//clear是自己写的函数
	}

	for (int i = 0; i < closeList.size(); i++) {
		
		map->mapCells[closeList[i].first - 1][closeList[i].second - 1].clear();
	}

	openList.clear();
	closeList.clear();

}


MapCell AStarPathfinding::getMapCellFromExcel(int x, int y)
{
	MapCell mc;
	mc.x = x;
	mc.x = x;
	mc.y = y;

	int value = excelTool->getNumericCellValue(x, y).toInt();
	switch (value)
	{
	case 0:
		mc.type = CellType::CELL_BLOCK;
		break;
	case 1:
		mc.type = CellType::CELL_ACCESSIBLE;
		break;
	case 2:
		mc.type = CellType::CELL_FETCH;
		break;
	case 3:
		mc.type = CellType::CELL_SHELF;
		break;
	case 4:
		mc.type = CellType::CELL_CASHIER;
		break;
	case 5:
		mc.type = CellType::CELL_STOREHOUSE;
		break;
	case 6:
		mc.type = CellType::CELL_STAFFROOM;
		break;
	case 7:
		mc.type = CellType::CELL_EXIT;
		break;
	case 8:
		mc.type = CellType::CELL_ENTRANCE;
		break;
	default:
		break;
	}

	return mc;
}

bool AStarPathfinding::isOutofBound(int x, int y)
{
	if (x < 1 || x> map->max_height|| y < 1 || y > map->max_width)
		return true;
	else return false;
}

float AStarPathfinding::getMinDist(int startX, int startY, int endX, int endY) {

	int x = abs(startX - endX);
	int y = abs(startY - endY);
	if (x <= y) {
		return x * slopeCoe + y - x;
	}
	else {
		return y * slopeCoe + x - y;
	}
}

//看是否在openList和closeList里，也就是不要getAround
bool AStarPathfinding::isDetected(int x, int y) {

	for (int i = 0; i < closeList.size(); i++)
		if (x == closeList[i].first && y == closeList[i].second)
			return true;
	for (int i = 0; i < openList.size(); i++)
		if (x == openList[i].first && y == openList[i].second)
			return true;

	return false;
}

MapCell* AStarPathfinding::getMinOpenMapCell() {

	MapCell* c = nullptr;
	float min = std::numeric_limits<float>::max();
	for (int i = 0; i < openList.size(); i++) {
		int x = openList[i].first;
		int y = openList[i].second;
		if (map->mapCells[x - 1][y - 1].F < min) {
			c = &map->mapCells[x - 1][y - 1];
			min = map->mapCells[x - 1][y - 1].F;
		}

	}

	return c;
}

void AStarPathfinding::getAround() {
	//计算1个格子周围的8个格子的F值
	float temp_G;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)continue;

			if (!isOutofBound(curMapCell->x + i, curMapCell->y + j)
				&& map->mapCells[curMapCell->x + i - 1][curMapCell->y + j - 1].isAccessible()) {
				MapCell* c = &map->mapCells[curMapCell->x + i - 1][curMapCell->y + j - 1];
				temp_G = curMapCell->G + (abs(i) + abs(j) == 2 ? slopeCoe : 1);

				//决定curMapCell是不是周围格子的parent
				if (isDetected(c->x,c->y)) {
					if ((temp_G - getMinDist(start->x, start->y, c->x, c->y))<std::numeric_limits<float>::epsilon()) {
						//当前格子可能是从原点到探测格子最近路径上的点
						c->parent = curMapCell;
					}

					//否则parent不变,有另外的最短路径到探测的这个格子
				}
				else {
					//没有探测过的格子，它的parent是curMapCell
					c->G = getMinDist(start->x, start->y, c->x, c->y);
					c->H = getMinDist(c->x, c->y, end->x, end->y);
					c->F = c->G + c->H;
					c->parent = curMapCell;
					openList.push_back(std::make_pair(c->x,c->y));
				}

			}

		}

}

void AStarPathfinding::moveToMinMapCell() {

	for (int i = 0; i < openList.size(); i++) {

		if (openList[i].first == curMapCell->x && openList[i].second == curMapCell->y) {
			auto op = openList.erase(openList.begin() + i);
		}

	}
	closeList.push_back(std::make_pair(curMapCell->x,curMapCell->y));
	curMapCell = getMinOpenMapCell();

}

vector<int> AStarPathfinding::getOrientedShelf(MapCell bef, MapCell next) {
	//vector<int> shelfSn;
	//int horizont = 3;

	//int x_orient = next.x - bef.x;
	//int y_orient = next.y - bef.y;

	//if (abs(x_orient) + abs(x_orient) == 2) {
	//	//斜向走
	//	int x = bef.x;
	//	int y = bef.y;
	//	while (x != bef.x + x_orient * (horizont - 1)) {
	//		if (!isOutofBound(x, y) && map->mapCells[x - 1][y - 1].type == CellType::CELL_SHELF && notInVector(shelfSn, map->mapCells[x - 1][y - 1].sn)) {
	//			shelfSn.push_back(map->mapCells[x - 1][y - 1].sn);
	//		}
	//		if (!isOutofBound(x, y + y_orient) && map->mapCells[x - 1][y - 1 + y_orient].type == CellType::CELL_SHELF && notInVector(shelfSn, map->mapCells[x - 1][y - 1 + y_orient].sn)) {
	//			shelfSn.push_back(map->mapCells[x - 1][y - 1 + y_orient].sn);
	//		}
	//		if (!isOutofBound(x, y + y_orient * 2) && map->mapCells[x - 1][y - 1 + y_orient * 2].type == CellType::CELL_SHELF && notInVector(shelfSn, map->mapCells[x - 1][y - 1 + y_orient * 2].sn)) {
	//			shelfSn.push_back(map->mapCells[x - 1][y - 1 + y_orient * 2].sn);
	//		}

	//		x += x_orient;
	//	}
	//}
	//else {
	//	//非斜向走
	//}

	return vector<int>();
}