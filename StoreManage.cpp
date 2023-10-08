#include "StoreManage.h"


StoreManage::StoreManage(QObject* parent, MapPanel * mapp, AStarPathfinding* as)
{
    setParent(parent);
    this->mapPanel = mapp;
    this->map = mapp->map;
    this->astar = as;
    customerPool = new QThreadPool(this);
    customerPool->setMaxThreadCount(10);
}


int StoreManage::commodityOnWhichFacility(int commoditySn)
{
    return commodityOnFacility[commoditySn-1];
}

void StoreManage::setCommodityOnFacility(int commoditySn, int facilitySn)
{
    if (commoditySn > commodityOnFacility.size())
    {
		commodityOnFacility.resize(commoditySn);
	}
	commodityOnFacility[commoditySn-1] = facilitySn;
}

void StoreManage::createCustomer(QVector<QPair<int, int>> aim)
{
    Customer* customer = new Customer(this,aim);
    customer->setAStarKit(astar);
    customer->setMapPanel(mapPanel);
    customer->setConnectConfig();
	customerList.push_back(customer);

}

void StoreManage::addCustomer(Customer* c)
{
    customerList.push_back(c);
}

void StoreManage::startSimulation()
{
    
    for (int i = 0; i < customerList.size(); i++)
    {
        
	}

    customerPool->waitForDone();


}

