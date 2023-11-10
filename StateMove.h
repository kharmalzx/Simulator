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
	//���ؿ����Ļ��ܱ��
	int watchDetect(MapCell* nextCell);
	int getShelfInHorizont(const int& x, const int& y);
	void moveToEnd(MapCell* end);
	void moveToRandomShelf();

	//moveToQueue������һ�д�move����ʩ��������ٴ�queue��������ʩ��״̬
	void toQueue();
	void toExit();
	void toMove() override;
};
