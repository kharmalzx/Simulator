#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <qgraphicsitem.h>
#include "Data.h"
#include "Map.h"

class MapPanel  : public QGraphicsScene
{
	Q_OBJECT

public:
	MapPanel(QObject *parent,Data* data);

	Map* map;

	void drawMap();

	QVector<QVector<QGraphicsRectItem*>> items;

public slots:
	void updateMap();

private:
	Data* data;
	

	
};
