#include "StoreManage.h"


StoreManage::StoreManage(QObject* parent, MapPanel * mapp, AStarPathfinding* as)
{
    setParent(parent);
    this->mapPanel = mapp;
    this->map = mapp->map;
    this->astar = as;

    shelfList.resize(map->shelfList.size());
    for (int i = 0; i < shelfList.size(); i++) { shelfList[i] = &map->shelfList[i]; }
}


int StoreManage::commodityOnWhichFacility(int commoditySn)
{
    for(int i=0;i<commodityOnFacility.size();i++)
		if (commodityOnFacility[i].first == commoditySn)
			return commodityOnFacility[i].second;
    return -1;
}

int StoreManage::facilityHasWhatCommodity(int facilitySn)
{
    for (int i = 0; i < facilityHasCommodity.size(); i++) {
        if(facilityHasCommodity[i].first == facilitySn)
			return facilityHasCommodity[i].second;
    }

    return -1;
}

int StoreManage::mapCellBelongsToWhichFacility(int x, int y)
{
    for (int i = 0; i < shelfList.size(); i++) {
        for (int j = 0; j < shelfList[i]->list_mapcell_area.size(); j++) {
            if(shelfList[i]->list_mapcell_area[j].x == x && shelfList[i]->list_mapcell_area[j].y == y)
                return shelfList[i]->sn;
        }
        for (int j = 0; j < shelfList[i]->list_mapcell_fetch.size(); j++) {
            if(shelfList[i]->list_mapcell_fetch[j].x == x && shelfList[i]->list_mapcell_fetch[j].y == y)
				return shelfList[i]->sn;
        }
        for (int j = 0; j < shelfList[i]->list_service_ports.size(); j++) {
            if(shelfList[i]->list_service_ports[j].x == x && shelfList[i]->list_service_ports[j].y == y)
                return shelfList[i]->sn;
		}
    }

    for (int i = 0; i < cashierList.size(); i++) {
        for(int j=0;j<cashierList[i]->list_mapcell_area.size();j++)
			if (cashierList[i]->list_mapcell_area[j].x == x && cashierList[i]->list_mapcell_area[j].y == y)
				return cashierList[i]->sn;

        for (int j = 0; j < cashierList[i]->list_mapcell_fetch.size(); j++)
            if (cashierList[i]->list_mapcell_fetch[j].x == x && cashierList[i]->list_mapcell_fetch[j].y == y)
                return cashierList[i]->sn;

        for (int j = 0; j < cashierList[i]->list_service_ports.size(); j++)
            if (cashierList[i]->list_service_ports[j].x == x && cashierList[i]->list_service_ports[j].y == y)
				return cashierList[i]->sn;
    }

    return -1;
}

void StoreManage::setCommodityOnFacility(int commoditySn, int facilitySn)
{
    for (int i = 0; i < commodityOnFacility.size(); i++) {
        if (commodityOnFacility[i].first == commoditySn) {
			commodityOnFacility[i].second = facilitySn;
			return;
		}
    }

    commodityOnFacility.push_back(QPair<int, int>(commoditySn, facilitySn));
}

void StoreManage::createCustomer(QVector<QPair<int, int>> aim)
{
    Customer* customer = new Customer(this,aim);
    customer->setAStarKit(astar);
    customer->setMapPanel(mapPanel);
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


}

