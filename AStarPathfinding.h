#pragma once
#include <algorithm>
#include <qthread.h>
#include <qmutex.h>
#include "Data.h"
#include "ExcelTool.h"

using std::pair;

class AStarPathfinding {

public:
	float slopeCoe = 1.5;
	

	AStarPathfinding();
	~AStarPathfinding();
	void readMap();
	void getShelfArea(MapCell cur, Shelf* sf);
	vector<MapCell> getPath(int startX, int startY, int endX, int endY);
	void resetMap();

    Data* data;

private:

	ExcelTool* excelTool;

	MapCell* start;
	MapCell* end;
	vector<pair<int,int>> openList;
	vector<pair<int,int>> closeList;
	
	Map* map;
	MapCell* curMapCell;

	QMutex getPathMutex;

	MapCell getMapCellFromExcel(int x, int y);
	bool isOutofBound(int x, int y);
	float getMinDist(int startX, int startY, int endX, int endY);
	bool isDetected(int x, int y);
	MapCell* getMinOpenMapCell();
	void getAround();
	void moveToMinMapCell();
	vector<int> getOrientedShelf(MapCell bef, MapCell next);
};