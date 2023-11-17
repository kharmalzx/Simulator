#pragma once
#include "MapCell.h"
#include "Commodity.h"
#include <qobject.h>
#include <qmutex.h>

class Facility : public QObject {

	Q_OBJECT
public:

	struct QueueCellInfo
	{
		int customerId;
		MapCell* cellAt;
	};

	int sn;
	int type;
	int maxStorage;
	int cur_population;
	int service_tick;
	QMutex commodityMutex;
	QMutex expectedMutex;
	

	QVector<MapCell> list_mapcell_area;
	QVector<MapCell> list_mapcell_fetch;
	QVector<MapCell> list_service_ports;
	//用于维护排队的顾客信息,它的第一个vector下标和list_service_ports或者list_mapcell_fetch的下标对应
	QVector<QVector<QueueCellInfo>> list_queue;

	void setSn(int sn) { this->sn = sn; }
	void setType(int type) { this->type = type; }
	void updateQueue(const int& fetchPoint, const int& customerId, MapCell* c);
	int valve() const { return m_valve; }
	void setValve(const int& valve) { m_valve = valve; }
	void setWorkCell(MapCell* cell) { m_workCell = cell; }
	MapCell* getWorkCell() { return m_workCell; }

signals:
	void adustQueueFormation();

private:
	//目前没有设置
	int m_valve;
	MapCell* m_workCell;
};

class Shelf : public Facility
{
public:

	using FetchSquare = QPair<int, MapCell*>;
	

	Shelf();
	~Shelf();

	int cur_count;
	//用这个量来记录这个货架上商品被预定取后的存量，因为可能会有人拿走，但是还没读条完
	int expected_count;
	Commodity m_commodity;
	//未初始化，first是属于哪个取货口组，second是mapcell
	QVector<FetchSquare> fetchGroup;
	

	void setCommodity(Commodity c) { m_commodity = c; }
	bool canFetchCommodity(const int& fetchCount);
	void realFetchCommodity(const int& fetchCount);
	void replenishCommodity();


private:

};


class Cashier : public Facility
{
public:

	Cashier();
	~Cashier();

};

