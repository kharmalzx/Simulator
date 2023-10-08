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
	vector<vector<MapCell>> paths; //������·��
	vector<vector<int> > shelvesInSight;  //��¼����path�и�·�����ܿ����Ļ��ܱ��

};

