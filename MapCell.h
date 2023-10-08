#pragma once
#include <memory>

enum CellType
{
	CELL_BLOCK = 0,
	CELL_ACCESSIBLE = 1,
	CELL_FETCH = 2,
	CELL_SHELF = 3,
	CELL_CASHIER = 4,
	CELL_STOREHOUSE = 5,
	CELL_STAFFROOM = 6,
	CELL_EXIT = 7,
	CELL_ENTRANCE = 8,
};

class MapCell
{
public:

	int x, y;
	CellType type;
	float F, G, H;  //F=G+H
	MapCell* parent;  //只有1个最优的parent

	MapCell();

	void clear();
	bool isAccessible();

};

