#include "StateMove.h"

StateMove::StateMove(QObject *parent) : AbstractCustomerState(parent)
{
    astar = new AStarPathfinding();
}

StateMove::~StateMove()
{}

void StateMove::setOwner(Customer * owner)
{
    this->owner = owner;
    
    storeManage = owner->storeManage;
    path = new QVector<MapCell*>();
    aimList = &owner->list_moveCell_aim;
    currentCell = owner->cellAt();

}

void StateMove::toMove()
{
    //如果目标为空，就随机找一个货架
    if (aimList->size() == 0) {
		moveToRandomShelf();
	}else{
		getPathInAimlist();
		moveToEnd((*aimList)[0]);
	}
}

MapCell* StateMove::cellAt(const int& x, const int& y) const
{
    if (x >= 0 && x < storeManage->getMapHeight() && y >= 0 && y < storeManage->getMapWidth())
    {
        return storeManage->getMapCell(x, y);
    }
}

void StateMove::getPathInAimlist()
{
    for (int i = 0; i < aimList->size() - 1; i++) {
        QVector<MapCell*> temp = astar->getPath(aimList->at(i)->x(), aimList->at(i)->y(), aimList->at(i+1)->x(), aimList->at(i+1)->y());
        int size_bf = path->size();
        if (i != 0) {
            path->resize(size_bf + temp.size() - 1);
            for (int j = 1; j < temp.size(); j++)
                (*path)[size_bf + j - 1] = temp[j];
        }
        else {
            path->resize(size_bf + temp.size());
            for (int j = 0; j < temp.size(); j++)
                (*path)[size_bf + j] = temp[j];
        }

    }

    //转换为路径后清空目标list
    aimList->clear();
}

int StateMove::watchDetect(MapCell* nextCell)
{
    //视野检测，从最远处看回来，而不是从原地看出去

    int shelfSn = 0;

    if (owner->AIData.horizont == 3) {
        //可以试试向量+点与点之间的距离看是否在视野范围内
        QPair<int, int> vec = QPair<int, int>(nextCell->x() - currentCell->x(), nextCell->y() - currentCell->y());

        for (int i = -1; i < owner->AIData.horizont - 1; i++) {
            for (int j = -1; j < owner->AIData.horizont - 1; j++) {
                if (shelfSn = getShelfInHorizont(nextCell->x() + i, nextCell->y() + j))return shelfSn;
            }
        }

        //走到nextCell会看到边缘的一部分视野
        if (abs(vec.first) + abs(vec.second) == 1) {
            //延长3格

            int pos_x = nextCell->x() + vec.first * 2;
            int pos_y = nextCell->y() + vec.second * 2;

            for (int i = abs(vec.first) - 1; i <= 1 - abs(vec.first); i++) {
                for (int j = abs(vec.second) - 1; j <= 1 - abs(vec.second); j++) {
                    if (shelfSn = getShelfInHorizont(pos_x + i, pos_y + j))return shelfSn;
                }
            }
        }
        else {
            //5格
            if (shelfSn = getShelfInHorizont(nextCell->x() + 2 * vec.first, nextCell->y()))return shelfSn;
            if (shelfSn = getShelfInHorizont(nextCell->x() + 2 * vec.first, nextCell->y() + 1 * vec.second))return shelfSn;
            if (shelfSn = getShelfInHorizont(nextCell->x() + 2 * vec.first, nextCell->y() + 2 * vec.second))return shelfSn;
            if (shelfSn = getShelfInHorizont(nextCell->x() + 1 * vec.first, nextCell->y() + 2 * vec.second))return shelfSn;
            if (shelfSn = getShelfInHorizont(nextCell->x(), nextCell->y() + 2 * vec.second))return shelfSn;
        }

    }
    else if (owner->AIData.horizont == 4) {

    }
    else if (owner->AIData.horizont == 5) {

    }

    return -1;
}

int StateMove::getShelfInHorizont(const int& x, const int& y)
{
    if (x >= 0 && x < storeManage->getMapHeight() && y >= 0 && y < storeManage->getMapWidth()) {
        if (cellAt(x,y)->type == CELL_SHELF || cellAt(x,y)->type == CELL_COMPLEX) {
            int shelfSn = storeManage->mapCellBelongsToWhichFacility(x, y);
            int commoditySn = storeManage->facilityHasWhatCommodity(shelfSn);

            CommodityNeed* cn = owner->getCommodityNeed(commoditySn);
            if (cn != nullptr) {
                owner->findCommoditySn = commoditySn;
                owner->list_shelf_detected.push_back(shelfSn);
                return shelfSn;
            }
            

        }
    }
}

void StateMove::moveToEnd(MapCell* end)
{
    if (path->size() == 0 || end == nullptr) {
        qDebug() << "寻路的路径为空或寻路目标不存在";
        return;
    }

    bool isToCashier = false;

    if (end->type == CELL_CASHIER) {
        isToCashier = true;
    }

    int facilitySn = -1;
    owner->setLoc(path->at(0));
    MapCell* nextCell = path->at(1);

    //播走路动画，应该是个while循环,路上查视野，去往收银台的时候不查
    if (!owner->isWatchForbidden()) {
        while ((facilitySn = watchDetect(nextCell)) < 0 && !isToCashier && (nextCell->x() != end->x() && nextCell->y() != end->y())) {
            path->pop_front();
            owner->setLoc(nextCell);
            nextCell = path->at(1);


        }
    }
    

    if (facilitySn) {
        //看到后，需要看设施人数是否超过容忍上限
        QPair<bool, bool> shallJoin = owner->storeManage->shallJoinQueue(owner, facilitySn);
        if (shallJoin.first) {
            //需要等待
            owner->queueInfo.isQueue = true;
            owner->queueInfo.facilitySn = facilitySn;
            owner->queueInfo.isInQueue1 = shallJoin.second;

            //以货架最近的取货口的队尾为终点,已经占用了
            //并且owner的fetchPoint在这里设置
            end = owner->storeManage->requestShortestQueueEnd(owner->AIData.id, facilitySn);

            if (end != nullptr) {
                path->clear();
                owner->list_moveCell_aim.clear();
                owner->list_moveCell_aim.push_back(end);

                storeManage->lockQueueEnd(owner, facilitySn);

                toMove();
                
            }
            else {
                qDebug() << "顾客" << owner->AIData.id << "找不到设施" << facilitySn << "的取货口/服务点的队尾";
            }

        }
        else {
            //不等待或者排队
            owner->queueInfo.isQueue = false;
            
        }

    }
    else {
        //再走一步到达终点
        currentCell = nextCell;
        owner->setLoc(nextCell);

        if (owner->queueInfo.isQueue) {
            //在队中，但在收银台，试衣间还是货架？返回值偷懒用CELL类型代替
            int faci_type = storeManage->getFacilityType(owner->queueInfo.facilitySn);
            switch (faci_type)
            {
                case CELL_CASHIER:
                    toQueue();
                    break;
                case CELL_SHELF:
                    toQueue();
                    break;
                case CELL_COMPLEX:
                    toQueue();
					break;
                case CELL_DRESSINGROOM:
                    toQueue();
                    break;
                case CELL_EXIT:
                    toExit();
                    break;
                case CELL_SOLICITAREA:
                    // 如果是在店外的顾客
                    if (storeManage->isSolicitSussessful()) {
                        moveToRandomShelf();
                        storeManage->customerCountChange(1);
                    }
                    else {
                        moveToEnd(storeManage->getDestroyCell());
                    }
                    break;
                case CELL_DESTROY:
                    //如果是在销毁点的顾客
                    
					break;
                default:
                    break;
            }
        }
        else {
            // 店内顾客到达普通格子，
            // 路上什么事情都没发生
            //不用改变状态，继续寻路
            toMove();
        }
    }
}

void StateMove::moveToRandomShelf()
{
    if (!aimList->isEmpty()) {
        //已经有目标了，不用再找随机货架
        getPathInAimlist();
        moveToEnd(aimList->at(0));
        return;
    }

    MapCell* randMapCell;

    //顾客随机寻路获取目标
    if (owner->list_shelf_detected.size() == storeManage->shelfList.size()) {
        //全都搜寻完了，判断是否买完了
        //如果



        //此处应该找举例结账点最近的队尾
        int rand = std::rand() % storeManage->cashierList.size();
        randMapCell = storeManage->requestShortestQueueEnd(owner->AIData.id, storeManage->cashierList[rand]->sn);
        aimList->push_back(randMapCell);
    }
    else {

        int rand = 0;
        while (owner->list_shelf_detected.contains(storeManage->shelfList[(rand = std::rand() % storeManage->shelfList.size())]->sn)) {}

        //在货架周围一圈内随机选一个点

        int rand_which = std::rand() % storeManage->shelfList[rand]->list_mapcell_area.size();
        int rand_pos = std::rand() % MapCell::circle_one.size();
        randMapCell = &storeManage->shelfList[rand]->list_mapcell_area[rand_which];

        while (astar->isOutofBound(randMapCell->x() + MapCell::circle_one[rand_pos].first, randMapCell->y() + MapCell::circle_one[rand_pos].second)
            || cellAt(randMapCell->x() + MapCell::circle_one[rand_pos].first,randMapCell->y() + MapCell::circle_one[rand_pos].second)->isAccessible())
        {
            rand_which = std::rand() % storeManage->shelfList[rand]->list_mapcell_area.size();
            rand_pos = std::rand() % MapCell::circle_one.size();
            randMapCell = &storeManage->shelfList[rand]->list_mapcell_area[rand_which];
        }


        aimList->push_back(cellAt(randMapCell->x() + MapCell::circle_one[rand_pos].first,randMapCell->y() + MapCell::circle_one[rand_pos].second));
    }

    getPathInAimlist();


    //然后走到终点
    moveToEnd(randMapCell);
}

void StateMove::toQueue()
{
    emit moveToQueue();
}

void StateMove::toExit()
{
    emit moveToExit();
}
