#pragma once
#include "Shelf.h"
#include <vector>
#include "MapCell.h"

using std::vector;

class Path
{
public:
	Path* nextSameStartPath;
	Path* nextSameEndPath;
	Shelf* start;
	Shelf* end;
	vector<vector<MapCell>> paths; //往返的路径
	vector<vector<int> > shelvesInSight;  //记录这条path中各路径中能看到的货架编号

};

