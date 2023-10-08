#include "MapCell.h"

MapCell::MapCell() {
	x = 1;
	y = 1;
	type = CELL_ACCESSIBLE;
	F = 200000;
	G = 100000;
	H = 100000;
	parent = nullptr;

	
}

void MapCell::clear()
{
	this->F = 200000;
	this->G = 100000;
	this->H = 100000;
	this->parent = nullptr;
}

bool MapCell::isAccessible()
{
	if (this->type == CELL_BLOCK || this->type == CELL_SHELF)
		return false;
	else return true;
}