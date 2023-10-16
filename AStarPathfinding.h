#pragma once
#include <algorithm>
#include <qthread.h>
#include <qmutex.h>
#include "Data.h"
#include "ExcelTool.h"


class AStarPathfinding {

public:
	float slopeCoe = 1.5;
	

	AStarPathfinding();
	~AStarPathfinding();
	void readMap();
	void getFacilityArea(MapCell cur, Facility* facility);
	QVector<MapCell> getPath(int startX, int startY, int endX, int endY);
	void resetMap();
	bool isOutofBound(int x, int y);


    Data* data;

private:

	ExcelTool* excelTool;

	MapCell* start;
	MapCell* end;
	QVector<QPair<int,int>> openList;
	QVector<QPair<int,int>> closeList;
	
	Map* map;
	MapCell* curMapCell;

	QMutex getPathMutex;

	MapCell getMapCellFromExcel(int x, int y);
	
	float getMinDist(int startX, int startY, int endX, int endY);
	bool isDetected(int x, int y);
	MapCell* getMinOpenMapCell();
	void getAround();
	void moveToMinMapCell();
	QVector<int> getOrientedShelf(MapCell bef, MapCell next);
};