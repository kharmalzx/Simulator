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


	Customer(int horizont, float speed, std::vector<int> needList, std::vector<int> detectList);
	Customer(QObject* parent, QVector<QPair<int, int>> aim);
	
	void drawCell();
	void setAStarKit(AStarPathfinding* as) { astar = as; };
	void setMapPanel(MapPanel* mp) { mapPanel = mp; };
	void setTimer(QTimer* t) { allTimer = t; };
	void setConnectConfig();
	void setThreadPool(QThreadPool* pThreadPool);
	QVector<MapCell> getPath();


signals:
	void purchaseStarted();
	void purchaseFinished();
	void checkoutStarted();
	void checkoutFinished();
	void queueStarted();
	void queueFinished();




public slots:
	


private:

	MapPanel* mapPanel;
	AStarPathfinding* astar;
	QThreadPool* threadPool;

	vector<int> needList;
	vector<int> detectList;

	QVector<QPair<int, int>> aimList;
	

	MapCell* start;
	MapCell* end;
	MapCell* curMapCell;
	QVector<MapCell> path;

	int x_before;
	int y_before;
	int x;
	int y;
	int count_timer = 0;
	QBrush comingBrush;
	QBrush leavingBrush;
	
	void getPathBySeq();
	
	QState* currentState;
	QStateMachine* c_machine;
	QVector<QState*> stateList;
	QVector<QAbstractTransition*> transitionList;

};

