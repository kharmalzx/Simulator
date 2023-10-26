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

	struct QuestInfo {
		bool isQueue;
		int facilitySn;
		MapCell* fetchPoint;
		int isInQueue1;
	};

	int id;
	int horizont;
	float speed;
	int num_tolerance;
	int waitWill;
	//first = 是否在队中, second = 在哪个设施的队中
	QuestInfo queueInfo;
	MapCell* pos_at;

	Customer(int id, int horizont, float speed, QVector<int> needList,QVector<int> detectedList);
	Customer(StoreManage* parent, QVector<MapCell*> aim);
	
	void setAStarKit(AStarPathfinding* as) { astar = as; };
	void setMapPanel(MapPanel* mp) { mapPanel = mp; };
	QVector<MapCell*> getPath();
	StoreManage* getParent() { return storeManage; };

	void moveToRandomShelf();
	void queue();
	QState getCurrentState();
	

private:

	StoreManage* storeManage;
	MapPanel* mapPanel;
	AStarPathfinding* astar;
	Map* map;
	CustomerMachine* machine;
	
	MapCell* currentCell;
	QVector<MapCell*> path;
	QVector<int> list_commodity_needs;
	QVector<int> list_shelf_detected;

	QVector<MapCell*> aimList;



	void getPathInAimlist();
	void initConnectToMachine();
	void initConnectToStoreManage();
	/// <summary>
	/// 返回看到的货架编号
	/// </summary>
	/// <param name="nextCell"></param>
	/// <returns></returns>
	int watchDetect(MapCell* nextCell);
	int getShelfInHorizont(const int& x, const int& y);
	void moveToEnd(MapCell* end);

	
	

signals:
	void sig_StateChange_moveToEnd();
	void sig_StateChange_moveToCheckout();
	void sig_StateChange_moveToPurchase();


	void updateQueue(Customer* customer, const int& facilitySn);

};

