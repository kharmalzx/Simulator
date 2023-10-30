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

    //ת��Ϊ·�������Ŀ��list
    aimList.clear();
}

void Customer::initConnectToMachine()
{
    
    connect(this, &Customer::sig_StateChange_moveToEnd, machine, &CustomerMachine::rec_fromOwner_moveToEnd);
    connect(this, &Customer::sig_StateChange_moveToCheckout, machine, &CustomerMachine::rec_fromOwner_moveToCheckout);
    connect(this, &Customer::sig_StateChange_moveToPurchase, machine, &CustomerMachine::rec_fromOwner_moveToPurchase);


    //���źŴ���ִ�е�֪ͨ�����ð�������ȥ�������Ա�޸ĸ��ڵ�
    connect(machine, &CustomerMachine::sig_toOwner_moveToRandomShelf, this, &Customer::moveToRandomShelf);
    connect(machine, &CustomerMachine::sig_toOwner_moveToPurchase, this, &Customer::queue);
    
}

void Customer::initConnectToStoreManage()
{
    connect(this, &Customer::updateQueue, storeManage, &StoreManage::updateQueue);
}

int Customer::watchDetect(MapCell* nextCell)
{
    //��Ұ��⣬����Զ���������������Ǵ�ԭ�ؿ���ȥ
    
    int shelfSn = 0;

    if (horizont == 3) {
        //������������+�����֮��ľ��뿴�Ƿ�����Ұ��Χ��
        QPair<int, int> vec = QPair<int, int>(nextCell->x - currentCell->x, nextCell->y - currentCell->y);

        for (int i = -1; i < horizont - 1; i++) {
            for (int j = -1; j < horizont - 1; j++) {
                if(shelfSn = getShelfInHorizont(nextCell->x + i, nextCell->y + j))return shelfSn;
            }
        }

        //�ߵ�nextCell�ῴ����Ե��һ������Ұ
        if (abs(vec.first) + abs(vec.second) == 1) {
            //�ӳ�3��
            
            int pos_x = nextCell->x + vec.first * 2;
            int pos_y = nextCell->y + vec.second * 2;

            for (int i = abs(vec.first) - 1; i <= 1 - abs(vec.first);i++){
                for (int j = abs(vec.second) - 1; j <= 1 - abs(vec.second); j++) {
                    if (shelfSn = getShelfInHorizont(pos_x + i,pos_y+j))return shelfSn;
                }
            }
        }
        else {
            //5��
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
                //������û�����Ʒ�ͷ���
                list_commodity_needs.removeOne(commoditySn);
                list_shelf_detected.push_back(shelfSn);
                return shelfSn;
            }
            else {
                //�����˾͵Ǽ�
                list_shelf_detected.push_back(shelfSn);
            }

        }
    }
}

void Customer::moveToEnd(MapCell* end)
{
    if (path.size() == 0 || end == nullptr) {
        qDebug() << "Ѱ·��·��Ϊ�ջ�Ѱ·Ŀ�겻����";
        return;
    }

    bool isToCashier = false;

    if (end->type == CELL_CASHIER) {
        isToCashier = true;
    }

    int facilitySn = -1;
    currentCell = &map->mapCells[path[0]->x][path[0]->y];
    MapCell* nextCell = &map->mapCells[path[1]->x][path[1]->y];

    //����·������Ӧ���Ǹ�whileѭ��,·�ϲ���Ұ��ȥ������̨��ʱ�򲻲�
    while ((facilitySn = watchDetect(nextCell)) < 0 && !isToCashier && (nextCell->x != end->x && nextCell->y!= end->y)) {
        path.pop_front();
	    currentCell = nextCell;
		nextCell = &map->mapCells[path[1]->x][path[1]->y];


    }
    
    if (facilitySn) {
        //��������Ҫ����ʩ�����Ƿ񳬹���������
        QPair<bool, bool> shallJoin = storeManage->shallJoinQueue(this, facilitySn);
        if (shallJoin.first) {
			//��Ҫ�ȴ�
            queueInfo.isQueue = true;
            queueInfo.facilitySn = facilitySn;
            queueInfo.isInQueue1 = shallJoin.second;

            //�Ի��������ȡ���ڵĶ�βΪ�յ�,�Ѿ�ռ����
            end = storeManage->requestShortestQueueEnd(id, facilitySn);

            if (end != nullptr) {
                path.clear();
                aimList.clear();
                aimList.push_back(end);

                //���ʽѰ·
                emit sig_StateChange_moveToEnd();
            }
            else {
                qDebug() << "�˿�" << id << "�Ҳ�����ʩ" << facilitySn << "��ȡ����/�����Ķ�β";
            }

		}
        else {
			//���ȴ�
            queueInfo.isQueue = false;
		}

    }
    else {
		//����һ�������յ�
        currentCell = nextCell;

        //�ж��յ�����ʲô����������������Ϊ
        if (queueInfo.isQueue) {
            //�ڶ��У���������̨�����¼仹�ǻ��ܣ�����ֵ͵����CELL���ʹ���
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
            //������ͨ���ӣ�·��ʲô���鶼û����
            //���øı�״̬������Ѱ·
            moveToRandomShelf();
        }
	}
			
}


void Customer::moveToRandomShelf()
{
    if (!aimList.isEmpty()){
        //�Ѿ���Ŀ���ˣ����������������
        getPathInAimlist();
        moveToEnd(aimList[0]);
        return;
    }
        

    MapCell* randMapCell;

    //�˿����Ѱ·��ȡĿ��
    if (list_shelf_detected.size() == storeManage->shelfList.size()) {
        //ȫ����Ѱ���ˣ��ж��Ƿ�������
        


        //�˴�Ӧ���Ҿ������˵�����Ķ�β
        int rand = std::rand() % storeManage->cashierList.size();
        randMapCell = storeManage->requestShortestQueueEnd(id, storeManage->cashierList[rand]->sn);
        aimList.push_back(randMapCell);
    }
    else {

        int rand = 0;
        while(list_shelf_detected.contains(storeManage->shelfList[(rand = std::rand() % storeManage->shelfList.size())]->sn)){}

        //�ڻ�����ΧһȦ�����ѡһ����
        
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
    

    //Ȼ���ߵ��յ�
    moveToEnd(randMapCell);
}

void Customer::queue()
{
    emit updateQueue(this,queueInfo.facilitySn);


    //�ɹ�����ȥ���˵���·״̬
    emit sig_StateChange_moveToEnd();

}

QState Customer::getCurrentState()
{  
    if(machine->configuration().values()[0])
        return qobject_cast<QState>(machine->configuration().values()[0]);
    else
        qDebug() << "���ܻ�õ�ǰ״̬";
}

QVector<MapCell*> Customer::getPath()
{
    return path;
}
