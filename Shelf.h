#pragma once
#include "MapCell.h"
#include "Commodity.h"
#include <vector>

using std::vector;

class Shelf
{
public:

	int sn;
	vector<MapCell> area;
	vector<MapCell> fetchList;
	Commodity m_commodity;

	Shelf();
	~Shelf();

	
};

