#pragma once
#include "Map.h"
#include <qtimer.h>
#include <qrunnable.h>
#include <qthreadpool.h>
#include <qthread.h>
#include "MapPanel.h"
#include "AStarPathfinding.h"
#include <qevent.h>
#include <qparallelanimationgroup.h>
#include <qpropertyanimation.h>
#include <qstatemachine.h>
#include <qsequentialanimationgroup.h>
#include <qabstracttransition.h>
#include "CustomerStates.h"
#include "StoreManage.h"


class Customer : public QObject
{
	Q_OBJECT
public:

	class CustomerTask : public QRunnable {
	public:

		void writePath();

	};

	int horizont;
	float speed;
	QTimer* allTimer;
	CustomerTask* customerTask;


	Customer(int horizont, float speed, QVector<int> needList,QVector<int> detectedList);
	Customer(StoreManage* parent, QVector<QPair<int, int>> aim);
	
	void setAStarKit(AStarPathfinding* as) { astar = as; };
	void setMapPanel(MapPanel* mp) { mapPanel = mp; };
	void setTimer(QTimer* t) { allTimer = t; };
	QVector<MapCell> getPath();
	StoreManage* getParent() { return storeManage; };

	void moveToRandomShelf();

signals:
	void purchaseStarted();
	void purchaseToMove();
	void checkoutStart();
	void checkoutFinished();
	void queueStarted();
	void queueFinished();
	void enter();
	void exit();
	void moveToCheckout();





public slots:
	

private:

	StoreManage* storeManage;
	MapPanel* mapPanel;
	AStarPathfinding* astar;
	Map* map;

	QVector<int> list_commodity_needs;
	QVector<int> list_shelf_detected;

	//QPairÊÇ×ø±êx,y
	QVector<MapCell> aimList;
	
	MapCell* start;
	MapCell* end;
	MapCell* curMapCell;
	QVector<MapCell> path;
	

	QState* currentState;
	QStateMachine* c_machine;

	void getPathInAimlist();
	void initStateMachine();
	void movetoEnd();
	
};

