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

	int max_height;
	int max_width;

	Map();
	~Map();
};

