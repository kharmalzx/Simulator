#include "Room.h"

Room::Room(QObject *parent)
	: QObject(parent)
{}

Room::~Room()
{}

int Room::type() const
{
	return m_type;
}

MapCell* Room::getCell(int x, int y) const
{
	return m_area[x][y];
}
