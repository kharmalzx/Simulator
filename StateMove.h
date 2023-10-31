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

	void OnInterruption() override;

signals:
	void moveToQueue();

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

	void ToQueue();
	void ToFetch();
	void ToCheckout();

	void ToMove() override;
};
