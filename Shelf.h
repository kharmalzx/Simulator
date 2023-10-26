#pragma once
#include "MapCell.h"
#include "Commodity.h"
#include <qobject.h>

class Facility : public QObject {

public:

	struct QueueCellInfo
	{
		int customerId;
		MapCell* cellAt;
	};

	int sn;
	int type;
	int max_size;
	int cur_population;

	QVector<MapCell> list_mapcell_area;
	QVector<MapCell> list_mapcell_fetch;
	QVector<MapCell> list_service_ports;
	//用于维护排队的顾客信息,它的第一个vector下标和list_service_ports或者list_mapcell_fetch的下标对应
	QVector<QVector<QueueCellInfo>> list_queue;

	void setSn(int sn) { this->sn = sn; }
	void setType(int type) { this->type = type; }
	void updateQueue(const int& fetchPoint, const int& customerId, MapCell* c);

};

class Shelf : public Facility
{
public:

	using FetchSquare = QPair<int, MapCell*>;
	

	Shelf();
	~Shelf();


	Commodity m_commodity;
	//未初始化，first是属于哪个取货口组，second是mapcell
	QVector<FetchSquare> fetchGroup;
	

	void setCommodity(Commodity c) { m_commodity = c; }
	

};


class Cashier : public Facility
{
public:

	Cashier();
	~Cashier();

};

