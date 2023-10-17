#pragma once
#include "Customer.h"
#include "ExcelTool.h"

class StoreManage : public QObject
{
	Q_OBJECT
public:

	

	StoreManage(QObject* parent, MapPanel* mapPanel,AStarPathfinding* astar);

	int commodityOnWhichFacility(int commoditySn);
	int facilityHasWhatCommodity(int facilitySn);
	int mapCellBelongsToWhichFacility(int x, int y);
	void setCommodityOnFacility(int commoditySn, int facilitySn);
	void createCustomer(QVector<QPair<int, int>> aim);
	void addCustomer(Customer* c);
	void startSimulation();

	//店铺信息管理
	QVector<Shelf*> shelfList;
	QVector<Customer*> customerList;
	QVector<Cashier*> cashierList;
	

private:

	AStarPathfinding* astar;
	
	MapPanel* mapPanel;
	Map* map;

	//first = commoditySn, second = facilitySn
	QVector<QPair<int,int>> commodityOnFacility;
	//first = facilitySn, second = commoditySn
	QVector<QPair<int,int>> facilityHasCommodity;

signals:
	
};
