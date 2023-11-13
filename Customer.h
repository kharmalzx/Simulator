#pragma once

#include <qevent.h>
#include <qparallelanimationgroup.h>
#include <qpropertyanimation.h>
#include <qstatemachine.h>
#include <qsequentialanimationgroup.h>
#include <qabstracttransition.h>
#include "CustomerMachine.h"
#include "AStarPathfinding.h"
#include "CustomerInfo.h"


class Customer : public QObject
{
	Q_OBJECT
public:
	
	Customer(QObject* parent);
	
	QueueInfo queueInfo;
	CustomerAIData AIData;
	StoreKnowledge storeKnowledge;
	StoreManage* storeManage;

	CustomerMachine* machine;	

	QVector<int> list_shelf_detected;
	QVector<MapCell*> list_moveCell_aim;
	int findCommoditySn;

	
	void setAIData(CustomerAIData aiData) { AIData = aiData; };
	void animationMoveTo(MapCell* next);
	void check_if_queueStateChange();
	QState getCurrentState();
	CommodityNeed* getCommodityNeed(const int& commoditySn);
	MapCell* cellAt() const { return currentCell; }
	void setLoc(MapCell* cell) { *currentCell = *cell; }
	
	//检查状态，通知相关
	void checkAfterRepl();

signals:
	void checkQueueStateChange();
	void checkFetch();

private:
	MapCell* currentCell;
};

