#pragma once
#include "Customer.h"
#include "ExcelTool.h"

class StoreManage : public QObject
{
	Q_OBJECT
public:

	

	StoreManage(QObject* parent, MapPanel* mapPanel,AStarPathfinding* astar);

	int commodityOnWhichFacility(int commoditySn);
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
	QVector<int> commodityOnFacility;
	MapPanel* mapPanel;
	Map* map;

	QThreadPool* customerPool;
	

signals:
	
};
