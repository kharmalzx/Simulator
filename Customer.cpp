#include "Customer.h"

Customer::Customer(int id, int horizont, float speed, QVector<int> needList, QVector<int> detectedList)
{
	this->horizont = horizont;
	this->speed = speed;
	this->list_commodity_needs = needList;
	this->list_shelf_detected = detectedList;

}

Customer::Customer(StoreManage* parent, QVector<MapCell*> aim)
{
    setParent(parent);
    storeManage = parent;
    map = mapPanel->map;

    machine = new CustomerMachine(this,this);
    initConnectToMachine();

	
    for (int i = 0; i < aim.size(); i++) {
        aimList.push_back(aim[i]);
    }

}

void Customer::getPathInAimlist()
{
    for (int i = 0; i < aimList.size() - 1; i++) {
        QVector<MapCell*> temp = astar->getPath(aimList[i]->x, aimList[i]->y, aimList[i + 1]->x, aimList[i + 1]->y);
        int size_bf = path.size();
        if (i != 0) {
            path.resize(size_bf + temp.size() - 1);
            for (int j = 1; j < temp.size(); j++)
                path[size_bf + j - 1] = temp[j];
        }
        else {
            path.resize(size_bf + temp.size());
            for (int j = 0; j < temp.size(); j++)
                path[size_bf + j] = temp[j];
        }

    }

    //转换为路径后清空目标list
    aimList.clear();
}

void Customer::initConnectToMachine()
{
    
    connect(this, &Customer::sig_StateChange_moveToEnd, machine, &CustomerMachine::rec_fromOwner_moveToEnd);
    connect(this, &Customer::sig_StateChange_moveToCheckout, machine, &CustomerMachine::rec_fromOwner_moveToCheckout);
    connect(this, &Customer::sig_StateChange_moveToPurchase, machine, &CustomerMachine::rec_fromOwner_moveToPurchase);


    //用信号传递执行的通知，不用把自身传进去，避免成员修改父节点
    connect(machine, &CustomerMachine::sig_toOwner_moveToRandomShelf, this, &Customer::moveToRandomShelf);
    connect(machine, &CustomerMachine::sig_toOwner_moveToPurchase, this, &Customer::queue);
    
}

void Customer::initConnectToStoreManage()
{
    connect(this, &Customer::updateQueue, storeManage, &StoreManage::updateQueue);
}

int Customer::watchDetect(MapCell* nextCell)
{
    //视野检测，从最远处看回来，而不是从原地看出去
    
    int shelfSn = 0;

    if (horizont == 3) {
        //可以试试向量+点与点之间的距离看是否在视野范围内
        QPair<int, int> vec = QPair<int, int>(nextCell->x - currentCell->x, nextCell->y - currentCell->y);

        for (int i = -1; i < horizont - 1; i++) {
            for (int j = -1; j < horizont - 1; j++) {
                if(shelfSn = getShelfInHorizont(nextCell->x + i, nextCell->y + j))return shelfSn;
            }
        }

        //走到nextCell会看到边缘的一部分视野
        if (abs(vec.first) + abs(vec.second) == 1) {
            //延长3格
            
            int pos_x = nextCell->x + vec.first * 2;
            int pos_y = nextCell->y + vec.second * 2;

            for (int i = abs(vec.first) - 1; i <= 1 - abs(vec.first);i++){
                for (int j = abs(vec.second) - 1; j <= 1 - abs(vec.second); j++) {
                    if (shelfSn = getShelfInHorizont(pos_x + i,pos_y+j))return shelfSn;
                }
            }
        }
        else {
            //5格
            if (shelfSn = getShelfInHorizont(nextCell->x + 2 * vec.first,nextCell->y))return shelfSn;
            if (shelfSn = getShelfInHorizont(nextCell->x + 2 * vec.first, nextCell->y + 1 * vec.second))return shelfSn;
            if (shelfSn = getShelfInHorizont(nextCell->x + 2 * vec.first, nextCell->y + 2 * vec.second))return shelfSn;
            if (shelfSn = getShelfInHorizont(nextCell->x + 1 * vec.first, nextCell->y + 2 * vec.second))return shelfSn;
            if (shelfSn = getShelfInHorizont(nextCell->x, nextCell->y + 2 * vec.second))return shelfSn;
        }
        
    }
    else if (horizont == 4) {

    }
    else if (horizont == 5) {

    }

    return -1;
}

int Customer::getShelfInHorizont(const int& x, const int& y)
{
    if (x >= 0 && x < map->mapCells.size() && y >= 0 && y < map->mapCells[0].size()) {
        if (map->mapCells[x][y].type == CELL_SHELF) {
            int shelfSn = storeManage->mapCellBelongsToWhichFacility(x, y);
            int commoditySn = storeManage->facilityHasWhatCommodity(shelfSn);
            if (list_commodity_needs.contains(commoditySn)) {
                //看见有没买的商品就返回
                list_commodity_needs.removeOne(commoditySn);
                list_shelf_detected.push_back(shelfSn);
                return shelfSn;
            }
            else {
                //看见了就登记
                list_shelf_detected.push_back(shelfSn);
            }

        }
    }
}

void Customer::moveToEnd(MapCell* end)
{
    if (path.size() == 0 || end == nullptr) {
        qDebug() << "寻路的路径为空或寻路目标不存在";
        return;
    }

    bool isToCashier = false;

    if (end->type == CELL_CASHIER) {
        isToCashier = true;
    }

    int facilitySn = -1;
    currentCell = &map->mapCells[path[0]->x][path[0]->y];
    MapCell* nextCell = &map->mapCells[path[1]->x][path[1]->y];

    //播走路动画，应该是个while循环,路上查视野，去往收银台的时候不查
    while ((facilitySn = watchDetect(nextCell)) < 0 && !isToCashier && (nextCell->x != end->x && nextCell->y!= end->y)) {
        path.pop_front();
	    currentCell = nextCell;
		nextCell = &map->mapCells[path[1]->x][path[1]->y];


    }
    
    if (facilitySn) {
        //看到后，需要看设施人数是否超过容忍上限
        QPair<bool, bool> shallJoin = storeManage->shallJoinQueue(this, facilitySn);
        if (shallJoin.first) {
			//需要等待
            queueInfo.isQueue = true;
            queueInfo.facilitySn = facilitySn;
            queueInfo.isInQueue1 = shallJoin.second;

            //以货架最近的取货口的队尾为终点,已经占用了
            end = storeManage->requestShortestQueueEnd(id, facilitySn);

            if (end != nullptr) {
                path.clear();
                aimList.clear();
                aimList.push_back(end);

                //打断式寻路
                emit sig_StateChange_moveToEnd();
            }
            else {
                qDebug() << "顾客" << id << "找不到设施" << facilitySn << "的取货口/服务点的队尾";
            }

		}
        else {
			//不等待
            queueInfo.isQueue = false;
		}

    }
    else {
		//再走一步到达终点
        currentCell = nextCell;

        //判断终点属于什么，决定接下来的行为
        if (queueInfo.isQueue) {
            //在队中，但在收银台，试衣间还是货架？返回值偷懒用CELL类型代替
            pos_at = currentCell;

            if (storeManage->getFacilityType(queueInfo.facilitySn) == CELL_CASHIER) {

                emit sig_StateChange_moveToCheckout();
            }
            else if (storeManage->getFacilityType(queueInfo.facilitySn) == CELL_SHELF) {
                queue();
                emit sig_StateChange_moveToPurchase();
                
            }
            else if (storeManage->getFacilityType(queueInfo.facilitySn) == CELL_COMPLEX) {

            }
            else if (storeManage->getFacilityType(queueInfo.facilitySn) == CELL_DRESSINGROOM) {

            }
            
        }
        else {
            //到达普通格子，路上什么事情都没发生
            //不用改变状态，继续寻路
            moveToRandomShelf();
        }
	}
			
}


void Customer::moveToRandomShelf()
{
    if (!aimList.isEmpty()){
        //已经有目标了，不用再找随机货架
        getPathInAimlist();
        moveToEnd(aimList[0]);
        return;
    }
        

    MapCell* randMapCell;

    //顾客随机寻路获取目标
    if (list_shelf_detected.size() == storeManage->shelfList.size()) {
        //全都搜寻完了，判断是否买完了
        


        //此处应该找举例结账点最近的队尾
        int rand = std::rand() % storeManage->cashierList.size();
        randMapCell = storeManage->requestShortestQueueEnd(id, storeManage->cashierList[rand]->sn);
        aimList.push_back(randMapCell);
    }
    else {

        int rand = 0;
        while(list_shelf_detected.contains(storeManage->shelfList[(rand = std::rand() % storeManage->shelfList.size())]->sn)){}

        //在货架周围一圈内随机选一个点
        
        int rand_which = std::rand() % storeManage->shelfList[rand]->list_mapcell_area.size();
        int rand_pos = std::rand() % MapCell::circle_one.size();
        randMapCell = &storeManage->shelfList[rand]->list_mapcell_area[rand_which];
        
        while(astar->isOutofBound(randMapCell->x + MapCell::circle_one[rand_pos].first, randMapCell->y + MapCell::circle_one[rand_pos].second) 
            ||  !map->mapCells[randMapCell->x + MapCell::circle_one[rand_pos].first][ randMapCell->y + MapCell::circle_one[rand_pos].second].isAccessible())
        {
            rand_which = std::rand() % storeManage->shelfList[rand]->list_mapcell_area.size();
            rand_pos = std::rand() % MapCell::circle_one.size();
            randMapCell = &storeManage->shelfList[rand]->list_mapcell_area[rand_which];
        }


        aimList.push_back(&map->mapCells[randMapCell->x + MapCell::circle_one[rand_pos].first][randMapCell->y + MapCell::circle_one[rand_pos].second]);
    }
    
    getPathInAimlist();
    

    //然后走到终点
    moveToEnd(randMapCell);
}

void Customer::queue()
{
    emit updateQueue(this,queueInfo.facilitySn);


    //成功后切去结账的走路状态
    emit sig_StateChange_moveToEnd();

}

QState Customer::getCurrentState()
{  
    if(machine->configuration().values()[0])
        return qobject_cast<QState>(machine->configuration().values()[0]);
    else
        qDebug() << "不能获得当前状态";
}

QVector<MapCell*> Customer::getPath()
{
    return path;
}
