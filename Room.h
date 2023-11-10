#pragma once

#include <QObject>
#include "MapCell.h"

enum RoomType {
	STAFFROOM,
	OFFICE,
	STOREHOUSE,
	DISTRIBUTIONROOM
};

class Room  : public QObject
{
	Q_OBJECT

public:
	Room(QObject *parent);
	~Room();

	int type() const;
	void setType(int type) { m_type = type; };
	MapCell* getCell(int x, int y) const;
	void setArea(QVector<QVector<MapCell*>> area) { m_area = area; };

private:
	int m_type;
	QVector<QVector<MapCell*>> m_area;
};

