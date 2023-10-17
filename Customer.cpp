#include "Customer.h"

Customer::Customer(int horizont, float speed, QVector<int> needList, QVector<int> detectedList)
{
	this->horizont = horizont;
	this->speed = speed;
	this->list_commodity_needs = needList;
	this->list_shelf_detected = detectedList;

	
}

Customer::Customer(StoreManage* parent, QVector<QPair<int, int>> aim)
{
    setParent(parent);
    storeManage = parent;
    map = mapPanel->map;

    machine = new CustomerMachine(this,this);
    initConnectToMachine();

	
    for (int i = 0; i < aim.size(); i++) {
        MapCell c;
        c.clear();
        c.x = aim[i].first;
        c.y = aim[i].second;
        aimList.push_back(c);
    }


}

void Customer::getPathInAimlist()
{
    for (int i = 0; i < aimList.size() - 1; i++) {
        QVector<MapCell> temp = astar->getPath(aimList[i].x, aimList[i].y, aimList[i + 1].x, aimList[i + 1].y);
        int size_bf = path.size();
        if (i != 0) {
            path.resize(size_bf + temp.size() - 1);
            for (int j = 1; j < temp.size(); j++)
                path[size_bf + j - 1] = temp[j];
        }
        else {
            path.resize(size_bf + temp.size());
            for (int j = 0; j < temp.size(); j++)
                path[size_bf + j] = temp[j];
        }

    }

    //转换为路径后清空目标list
    aimList.clear();
}

void Customer::initConnectToMachine()
{
    connect(this, &Customer::sig_moveToEnd, machine, &CustomerMachine::rec_moveToEnd);
    connect(this, &Customer::sig_moveToCheckout, machine, &CustomerMachine::rec_moveToCheckout);

}

int Customer::watchDetect(MapCell* nextCell)
{
    //视野检测
    if (horizont == 3) {
        for (int i = -1; i < horizont - 1; i++) {
            for (int j = -1; j < horizont - 1; j++) {
                if (nextCell->x + i >= 0 && nextCell->x + i < map->mapCells.size() && nextCell->y + j >= 0 && nextCell->y + j < map->mapCells[0].size())
                    if (map->mapCells[nextCell->x + i][nextCell->y + j].type == CELL_SHELF) {
                        int shelfSn = storeManage->mapCellBelongsToWhichFacility(nextCell->x + i, nextCell->y + j);
                        int commoditySn = storeManage->facilityHasWhatCommodity(shelfSn);
                        if (list_commodity_needs.contains(commoditySn)) {
                            //看见有没买的商品就返回
                            list_commodity_needs.removeOne(commoditySn);
                            list_shelf_detected.push_back(shelfSn);
                            return shelfSn;
                        }
                        else {
                            //看见了就登记
                            list_shelf_detected.push_back(shelfSn);
                        }
                            
                    }
            }
        }

        //走到nextCell会看到边缘的一部分视野
        if (abs(nextCell->x - currentCell->x) + abs(nextCell->y - currentCell->y) == 1) {
            //延长3格

        }
        else {
            //5格
        }
        
    }
    else if (horizont == 4) {

    }
    else if (horizont == 5) {

    }

    return -1;
}

void Customer::moveToEnd(MapCell* end)
{
    if (path.size() == 0 || end == nullptr) {
        qDebug() << "寻路的路径为空或寻路目标不存在";
        return;
    }

    bool isToCashier = false;

    if (end->type != CELL_CASHIER) {
        isToCashier = true;
    }

    int shelfSn = -1;
    currentCell = &map->mapCells[path[0].x][path[0].y];
    MapCell* nextCell = &map->mapCells[path[1].x][path[1].y];

    //播走路动画，应该是个while循环,路上查视野，去往收银台的时候不查
    while ((shelfSn = watchDetect(nextCell)) < 0 && !isToCashier && (nextCell->x != end->x && nextCell->y!= end->y)) {

        path.pop_front();
	    currentCell = nextCell;
		nextCell = &map->mapCells[path[1].x][path[1].y];
    }
    
    if (shelfSn) {
        list_shelf_detected.push_back(shelfSn);
        end->x = storeManage->shelfList[shelfSn]->list_mapcell_fetch[0].x;
		end->y = storeManage->shelfList[shelfSn]->list_mapcell_fetch[0].y;
        aimList.push_back(storeManage->shelfList[shelfSn]->list_mapcell_fetch[0]);

        //打断式寻路
        emit sig_moveToEnd();
    }
    else {
		//再走一步到达终点
        currentCell = nextCell;

        if (end->type == CELL_CASHIER) {
			//到达收银台
			//播放结账动画
			//播放离开动画
		}
        else {
			//到达货架
			//播放购物动画
			//播放离开动画
		}
	}
		
    
		
}

void Customer::moveToRandomShelf()
{
    if (!aimList.isEmpty()){
        //已经有目标了，不用再找随机货架
        getPathInAimlist();
        moveToEnd(&aimList[0]);
        return;
    }
        

    MapCell* randMapCell;

    //顾客随机寻路获取目标
    if (list_shelf_detected.size() == storeManage->shelfList.size()) {
        //全都搜寻完了，去结账
        int rand = std::rand() % storeManage->cashierList.size();
        randMapCell = &storeManage->cashierList[rand]->list_mapcell_fetch[0];
        aimList.push_back(storeManage->cashierList[rand]->list_mapcell_fetch[0]);
    }
    else {

        int rand = 0;
        while(list_shelf_detected.contains(storeManage->shelfList[(rand = std::rand() % storeManage->shelfList.size())]->sn)){}

        //在货架周围一圈内随机选一个点
        
        int rand_which = std::rand() % storeManage->shelfList[rand]->list_mapcell_area.size();
        int rand_pos = std::rand() % MapCell::circle_one.size();
        randMapCell = &storeManage->shelfList[rand]->list_mapcell_area[rand_which];
        
        while(astar->isOutofBound(randMapCell->x + MapCell::circle_one[rand_pos].first, randMapCell->y + MapCell::circle_one[rand_pos].second) 
            ||  !map->mapCells[randMapCell->x + MapCell::circle_one[rand_pos].first][ randMapCell->y + MapCell::circle_one[rand_pos].second].isAccessible())
        {
            rand_which = std::rand() % storeManage->shelfList[rand]->list_mapcell_area.size();
            rand_pos = std::rand() % MapCell::circle_one.size();
            randMapCell = &storeManage->shelfList[rand]->list_mapcell_area[rand_which];
        }


        aimList.push_back(map->mapCells[randMapCell->x + MapCell::circle_one[rand_pos].first][randMapCell->y + MapCell::circle_one[rand_pos].second]);
    }
    
    getPathInAimlist();
    

    //然后走到终点
    moveToEnd(randMapCell);
}

QState Customer::getCurrentState()
{  
    if(machine->configuration().values()[0])
        return qobject_cast<QState>(machine->configuration().values()[0]);
    else
        qDebug() << "不能获得当前状态";
}

QVector<MapCell> Customer::getPath()
{
    return path;
}

void Customer::CustomerTask::writePath()
{

}
