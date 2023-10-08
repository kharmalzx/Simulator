#pragma once
#include "Customer.h"
#include "ExcelTool.h"

class StoreManage : public QObject
{
	Q_OBJECT
public:

	vector<Customer*> customerList;

	StoreManage(QObject* parent, MapPanel* mapPanel,AStarPathfinding* astar);

	int commodityOnWhichFacility(int commoditySn);
	void setCommodityOnFacility(int commoditySn, int facilitySn);
	void createCustomer(QVector<QPair<int, int>> aim);
	void addCustomer(Customer* c);
	void startSimulation();


private:

	AStarPathfinding* astar;
	QVector<int> commodityOnFacility;
	MapPanel* mapPanel;
	Map* map;

	QThreadPool* customerPool;
	QVector<Shelf*> shelfList;

signals:
	
};
