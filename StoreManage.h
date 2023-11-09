#pragma once
#include "Customer.h"
#include "ExcelTool.h"
#include "UserRunningData.h"

class StoreManage : public QObject
{
	Q_OBJECT
public:

	

	StoreManage(QObject* parent, MapPanel* mapPanel,AStarPathfinding* astar);

	int commodityOnWhichFacility(int commoditySn);
	int facilityHasWhatCommodity(int facilitySn);
	int mapCellBelongsToWhichFacility(int x, int y);
	void setCommodityOnFacility(int commoditySn, int facilitySn);
	void createCustomer(QVector<MapCell*> aim);
	void addCustomer(Customer* c);
	void startSimulation();
	MapCell* requestShortestQueueEnd(const int& customerId, const int& shelfSn);
	MapCell* getRecentFacilityFetchPoint(const int& x, const int& y, const int& shelfSn);
	//目前还没按照需求站队伍
	MapCell* getMapCellUnoccupiedAround(const int& x, const int& y);

	//店铺信息管理
	QVector<Shelf*> shelfList;
	QVector<Customer*> customerList;
	QVector<Cashier*> cashierList;
	QVector<Commodity*> commodityList;
	int getMapHeight() const;
	int getMapWidth() const;
	int getFacilityPopulation(const int& facilitySn);
	MapCell* getMapCell(const int& x, const int& y) const;
	int posAtFetchList(const int& facilitySn, MapCell* c);
	int getFacilityType(const int& facilitySn);
	//返回值第一个bool表示是否等待，第二个bool true表示在队列1，false表示在队列2
	QPair<bool,bool> shallJoinQueue(Customer* customer, const int& facilitySn);

	Facility* getFaciPtr(const int& facilitySn);
	Customer* getCustomerPtr(const int& customerID);
	Commodity* getCommodityPtr(const int& commoditySn);

	//队列相关
	void queueAdjust(const int& facilitySn,MapCell* fetchPoint);
	void customerQueueMoveOne(const int& facilitySn, const int& customerID, MapCell* end);
	int getQueueLength(const int& facilitySn, const int& fetchPointOrd);
	bool canFetchOnFacility(const int& facilitySn, const int& fetchCount);
	void realFetchOnFacility(const int& facilitySn, const int& fetchCount);
	void requestQuitQueue(Customer* owner);

	//店员补货相关
	void alarmShelfFinishedRepl(const int& facilitySn);

	//结账相关
	void customerPay(Customer* customer);

public slots:
	void lockQueueEnd(Customer* customer, const int& facilitySn);


private:

	AStarPathfinding* astar;
	
	MapPanel* mapPanel;
	Map* map;
	UserRunningData* urdata;

	//first = commoditySn, second = facilitySn
	QVector<QPair<int,int>> commodityOnFacility;
	//first = facilitySn, second = commoditySn
	QVector<QPair<int,int>> facilityHasCommodity;


	
};
