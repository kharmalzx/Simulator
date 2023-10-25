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
#include "StoreManage.h"
#include "CustomerMachine.h"


class Customer : public QObject
{
	Q_OBJECT
public:

	int id;
	int horizont;
	float speed;


	Customer(int horizont, float speed, QVector<int> needList,QVector<int> detectedList);
	Customer(StoreManage* parent, QVector<QPair<int, int>> aim);
	
	void setAStarKit(AStarPathfinding* as) { astar = as; };
	void setMapPanel(MapPanel* mp) { mapPanel = mp; };
	QVector<MapCell> getPath();
	StoreManage* getParent() { return storeManage; };

	void moveToRandomShelf();
	QState getCurrentState();
	

private:

	StoreManage* storeManage;
	MapPanel* mapPanel;
	AStarPathfinding* astar;
	Map* map;
	CustomerMachine* machine;
	
	MapCell* currentCell;
	QVector<MapCell> path;
	QVector<int> list_commodity_needs;
	QVector<int> list_shelf_detected;

	QVector<MapCell> aimList;



	void getPathInAimlist();
	void initConnectToMachine();
	/// <summary>
	/// 返回看到的货架编号
	/// </summary>
	/// <param name="nextCell"></param>
	/// <returns></returns>
	int watchDetect(MapCell* nextCell);
	int getShelfInHorizont(const int& x, const int& y);
	void moveToEnd(MapCell* end);
	

signals:
	void sig_moveToEnd();
	void sig_moveToCheckout();
	void sig_moveToPurchase();

};

