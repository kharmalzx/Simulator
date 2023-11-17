#pragma once
#include "Shelf.h"
#include <qobject.h>

class Map : public QObject
{
public:

	QVector<QVector<MapCell>> mapCells;
	QVector<Shelf> shelfList;
	QVector<Cashier> cashierList;
	QVector<MapCell> exitArea;
	QVector<MapCell> entranceArea;
	//还没有找
	QVector<MapCell> solicitArea;

	//还没定
	MapCell* destroyCell;

	int max_height;
	int max_width;

	Map();
	~Map();
};

