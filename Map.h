#pragma once
#include "Shelf.h"

using std::vector;

class Map
{
public:

	vector<vector<MapCell>> mapCells;
	vector<Shelf> shelfList;
	vector<MapCell> exitArea;
	vector<MapCell> entranceArea;

	int max_height;
	int max_width;

	Map();
	~Map();
};

