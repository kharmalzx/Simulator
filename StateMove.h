#pragma once

#include <QState>
#include "Customer.h"
#include "AbstractCustomerState.h"

class StateMove  : public AbstractCustomerState
{
	Q_OBJECT

public:
	StateMove(QObject *parent);
	~StateMove();

	void setOwner(Customer* owner) override;
	

public slots:

	void onInterruption() override;

signals:
	void moveToQueue();
	void moveToExit();

private:
	Customer* owner;
	StoreManage* storeManage;
	QVector<MapCell*>* path;
	QVector<MapCell*>* aimList;
	AStarPathfinding* astar;

	MapCell* currentCell;

	MapCell* cellAt(const int& x, const int& y) const;
	void getPathInAimlist();
	//返回看到的货架编号
	int watchDetect(MapCell* nextCell);
	int getShelfInHorizont(const int& x, const int& y);
	void moveToEnd(MapCell* end);
	void moveToRandomShelf();

	//moveToQueue适用于一切从move到设施的情况，再从queue到各类设施的状态
	void toQueue();
	void toExit();
	void toMove() override;
};
