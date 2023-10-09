#pragma once
#include "MapCell.h"
#include "Commodity.h"
#include <qobject.h>

class Facility : public QObject {

public:
	int sn;
	int type;
	QVector<MapCell> list_mapcell_area;
	QVector<MapCell> list_mapcell_fetch;
	QVector<MapCell> list_service_ports;

	void setSn(int sn) { this->sn = sn; }
	void setType(int type) { this->type = type; }
};

class Shelf : public Facility
{
public:

	Commodity m_commodity;

	Shelf();
	~Shelf();

	void setCommodity(Commodity c) { m_commodity = c; }
};


class Cashier : public Facility
{
public:

	Cashier();
	~Cashier();

};

