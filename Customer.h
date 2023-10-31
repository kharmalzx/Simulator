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
	QVector<MapCell*> path;
	MapCell* currentCell;

	QVector<int> list_shelf_detected;
	QVector<MapCell*> aimList;

	
	void setAIData(CustomerAIData aiData) { AIData = aiData; };
	void animationMoveTo(MapCell* next);
	void check_if_queue2to1();
	QState getCurrentState();

signals:
	void checkQueueStateChange();

private:

};

