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

void StoreManage::createCustomer(QVector<MapCell*> aim)
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

MapCell* StoreManage::requestShortestQueueEnd(const int& customerId, const int& facilitySn)
{
    //计划是去最近的取货口组的人数最少的取货口，目前没判断最近的取货口组
    MapCell* endCell = nullptr;
    MapCell* fetchPoint = nullptr;
    int type = getFacilityType(facilitySn);
    Facility* faci = getFaciPtr(facilitySn);


    int minSize = 999999;
    for (int j = 0; j < faci->list_queue[j].size(); j++) {
        if (minSize > faci->list_queue[j].size()) {
            minSize = faci->list_queue[j].size();
            endCell = faci->list_queue[j][faci->list_queue[j].size() - 1].cellAt;
            fetchPoint = faci->list_queue[j][0].cellAt;
        }
    }

    //找到endCell周围未被占用的cell，并上锁
    endCell = getMapCellUnoccupiedAround(endCell->x, endCell->y);
    if (endCell != nullptr) {        
        customerList[posAtCustomerList(customerId)]->queueInfo.fetchPoint = fetchPoint;
        endCell->setOccupy(true);
    }
    
    return endCell;

}

MapCell* StoreManage::getRecentFacilityFetchPoint(const int& x, const int& y, const int& shelfSn)
{
    float minDistance = 999999;
    MapCell* recentCell = nullptr;

    //之后可能需要分辨sn的种类，比如货架，收银台，服务台
    int pos = posAtShelfList(shelfSn);

    for (int i = 0; i < shelfList[pos]->list_mapcell_fetch.size(); i++) {
        if (minDistance > sqrt(pow(shelfList[pos]->list_mapcell_fetch[i].x - x, 2) + pow(shelfList[pos]->list_mapcell_fetch[i].y - y, 2))) {
            minDistance = sqrt(pow(shelfList[pos]->list_mapcell_fetch[i].x - x, 2) + pow(shelfList[pos]->list_mapcell_fetch[i].y - y, 2));
            recentCell = &shelfList[pos]->list_mapcell_fetch[i];
        }
            
    }
    
    return recentCell;
}

MapCell* StoreManage::getMapCellUnoccupiedAround(const int& x, const int& y)
{
    int dist = 1;
    int max_cell_num = map->mapCells.size() * map->mapCells[0].size();

    int count = 1;
    
    //未考虑朝向
    while (count<max_cell_num) {

        for (int i = -dist; i <= dist; i++) {
            for (int j = abs(i) - dist; j <= dist - abs(i); j++) {
                if(x+i>0 && y+j>0 && x+i<map->max_height && y+i<map->max_width && !map->mapCells[x+i][y+j].isOccupied())
					return &map->mapCells[x + i][y + j];
            }
        }

        dist++;
        count++;
    }

    return nullptr;
}

int StoreManage::posAtShelfList(const int& shelfSn)
{
    for (int i = 0; i < shelfList.size(); i++)
        if (shelfList[i]->sn == shelfSn)
            return i;

    return -1;
}

int StoreManage::posAtCustomerList(const int& customerId)
{
    for (int i = 0; i < customerList.size(); i++)
        if (customerList[i]->id == customerId)
            return i;

    return -1;
}

int StoreManage::posAtFetchList(const int& facilitySn, MapCell* c)
{
    Facility* faci =getFaciPtr(facilitySn);

    for (int i = 0; i < faci->list_mapcell_fetch.size(); i++) {
        if (faci->list_mapcell_fetch[i].x == c->x && faci->list_mapcell_fetch[i].y == c->y)
			return i;
    }
}

int StoreManage::getFacilityType(const int& facilitySn)
{
    if (facilitySn > 100) {
        return CELL_SHELF;
    }
    else
    {
        return CELL_CASHIER;
    }
}

QPair<bool, bool> StoreManage::shallJoinQueue(Customer* customer, const int& facilitySn)
{
    Facility* facility = getFaciPtr(facilitySn);

    if (facility->cur_population >= customer->num_tolerance) {
        if (customer->waitWill > 0) {
            return qMakePair(true,false);
        }
        else {
            return qMakePair(false,false);
        }
    }
    else {
        return qMakePair(true, true);
    }
	
}

Facility* StoreManage::getFaciPtr(const int& facilitySn)
{
    Facility* faci = nullptr;
    if(getFacilityType(facilitySn) == CELL_SHELF)
		faci = shelfList[posAtShelfList(facilitySn)];
	else if (getFacilityType(facilitySn) == CELL_CASHIER)
		faci = cashierList[posAtShelfList(facilitySn)];
    else if (getFacilityType(facilitySn) == CELL_COMPLEX) {

    }
    else if (getFacilityType(facilitySn) == CELL_DRESSINGROOM) {

    }
    return faci;
}

void StoreManage::updateQueue(Customer* customer, const int& facilitySn){
    Facility* facility = getFaciPtr(facilitySn);

    facility->updateQueue(posAtFetchList(facilitySn,customer->queueInfo.fetchPoint), customer->id, customer->pos_at);

}