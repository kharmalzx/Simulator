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
    path = &owner->path;
    aimList = &owner->list_moveCell_aim;
    currentCell = owner->currentCell;

}

void StateMove::ToMove()
{
    //���Ŀ��Ϊ�գ��������һ������
    if (aimList->size() == 0) {
		moveToRandomShelf();
	}else{
		getPathInAimlist();
		moveToEnd((*aimList)[0]);
	}
}

MapCell* StateMove::cellAt(const int& x, const int& y) const
{
    return storeManage->getMapCell(x,y);
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

    //ת��Ϊ·�������Ŀ��list
    aimList->clear();
}

int StateMove::watchDetect(MapCell* nextCell)
{
    //��Ұ��⣬����Զ���������������Ǵ�ԭ�ؿ���ȥ

    int shelfSn = 0;

    if (owner->AIData.horizont == 3) {
        //������������+�����֮��ľ��뿴�Ƿ�����Ұ��Χ��
        QPair<int, int> vec = QPair<int, int>(nextCell->x() - currentCell->x(), nextCell->y() - currentCell->y());

        for (int i = -1; i < owner->AIData.horizont - 1; i++) {
            for (int j = -1; j < owner->AIData.horizont - 1; j++) {
                if (shelfSn = getShelfInHorizont(nextCell->x() + i, nextCell->y() + j))return shelfSn;
            }
        }

        //�ߵ�nextCell�ῴ����Ե��һ������Ұ
        if (abs(vec.first) + abs(vec.second) == 1) {
            //�ӳ�3��

            int pos_x = nextCell->x() + vec.first * 2;
            int pos_y = nextCell->y() + vec.second * 2;

            for (int i = abs(vec.first) - 1; i <= 1 - abs(vec.first); i++) {
                for (int j = abs(vec.second) - 1; j <= 1 - abs(vec.second); j++) {
                    if (shelfSn = getShelfInHorizont(pos_x + i, pos_y + j))return shelfSn;
                }
            }
        }
        else {
            //5��
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
        qDebug() << "Ѱ·��·��Ϊ�ջ�Ѱ·Ŀ�겻����";
        return;
    }

    bool isToCashier = false;

    if (end->type == CELL_CASHIER) {
        isToCashier = true;
    }

    int facilitySn = -1;
    owner->currentCell = cellAt(owner->path[0]->x(), owner->path[0]->y());
    MapCell* nextCell = cellAt(owner->path[1]->x(), owner->path[1]->y());

    //����·������Ӧ���Ǹ�whileѭ��,·�ϲ���Ұ��ȥ������̨��ʱ�򲻲�
    while ((facilitySn = watchDetect(nextCell)) < 0 && !isToCashier && (nextCell->x() != end->x() && nextCell->y() != end->y())) {
        owner->path.pop_front();
        owner->currentCell = nextCell;
        nextCell = cellAt(owner->path[1]->x(), owner->path[1]->y());


    }

    if (facilitySn) {
        //��������Ҫ����ʩ�����Ƿ񳬹���������
        QPair<bool, bool> shallJoin = owner->storeManage->shallJoinQueue(owner, facilitySn);
        if (shallJoin.first) {
            //��Ҫ�ȴ�
            owner->queueInfo.isQueue = true;
            owner->queueInfo.facilitySn = facilitySn;
            owner->queueInfo.isInQueue1 = shallJoin.second;

            //�Ի��������ȡ���ڵĶ�βΪ�յ�,�Ѿ�ռ����
            //����owner��fetchPoint����������
            end = owner->storeManage->requestShortestQueueEnd(owner->AIData.id, facilitySn);

            if (end != nullptr) {
                owner->path.clear();
                owner->list_moveCell_aim.clear();
                owner->list_moveCell_aim.push_back(end);

                storeManage->lockQueueEnd(owner, facilitySn);

                ToMove();
                
            }
            else {
                qDebug() << "�˿�" << owner->AIData.id << "�Ҳ�����ʩ" << facilitySn << "��ȡ����/�����Ķ�β";
            }

        }
        else {
            //���ȴ������Ŷ�
            owner->queueInfo.isQueue = false;
            
        }

    }
    else {
        //����һ�������յ�
        currentCell = nextCell;

        //�ж��յ�����ʲô����������������Ϊ
        if (owner->queueInfo.isQueue) {
            //�ڶ��У���������̨�����¼仹�ǻ��ܣ�����ֵ͵����CELL���ʹ���
            
            if (storeManage->getFacilityType(owner->queueInfo.facilitySn) == CELL_CASHIER) {
                ToCheckout();
                
            }
            else if (storeManage->getFacilityType(owner->queueInfo.facilitySn) == CELL_SHELF) {
                
                ToQueue();
            }
            else if (storeManage->getFacilityType(owner->queueInfo.facilitySn) == CELL_COMPLEX) {

            }
            else if (storeManage->getFacilityType(owner->queueInfo.facilitySn) == CELL_DRESSINGROOM) {

            }

        }
        else {
            //������ͨ���ӣ�·��ʲô���鶼û����
            //���øı�״̬������Ѱ·
            ToMove();
        }
    }
}

void StateMove::moveToRandomShelf()
{
    if (!aimList->isEmpty()) {
        //�Ѿ���Ŀ���ˣ����������������
        getPathInAimlist();
        moveToEnd(aimList->at(0));
        return;
    }

    MapCell* randMapCell;

    //�˿����Ѱ·��ȡĿ��
    if (owner->list_shelf_detected.size() == storeManage->shelfList.size()) {
        //ȫ����Ѱ���ˣ��ж��Ƿ�������
        //���



        //�˴�Ӧ���Ҿ������˵�����Ķ�β
        int rand = std::rand() % storeManage->cashierList.size();
        randMapCell = storeManage->requestShortestQueueEnd(owner->AIData.id, storeManage->cashierList[rand]->sn);
        aimList->push_back(randMapCell);
    }
    else {

        int rand = 0;
        while (owner->list_shelf_detected.contains(storeManage->shelfList[(rand = std::rand() % storeManage->shelfList.size())]->sn)) {}

        //�ڻ�����ΧһȦ�����ѡһ����

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


    //Ȼ���ߵ��յ�
    moveToEnd(randMapCell);
}

void StateMove::ToQueue()
{
    emit moveToQueue();
}

void StateMove::ToCheckout()
{
}
