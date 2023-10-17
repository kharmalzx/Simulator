#include "Customer.h"

Customer::Customer(int horizont, float speed, QVector<int> needList, QVector<int> detectedList)
{
	this->horizont = horizont;
	this->speed = speed;
	this->list_commodity_needs = needList;
	this->list_shelf_detected = detectedList;

	
}

Customer::Customer(StoreManage* parent, QVector<QPair<int, int>> aim)
{
    setParent(parent);
    storeManage = parent;
    map = mapPanel->map;

    machine = new CustomerMachine(this,this);
    initConnectToMachine();

	
    for (int i = 0; i < aim.size(); i++) {
        MapCell c;
        c.clear();
        c.x = aim[i].first;
        c.y = aim[i].second;
        aimList.push_back(c);
    }


}

void Customer::getPathInAimlist()
{
    for (int i = 0; i < aimList.size() - 1; i++) {
        QVector<MapCell> temp = astar->getPath(aimList[i].x, aimList[i].y, aimList[i + 1].x, aimList[i + 1].y);
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
    connect(this, &Customer::sig_moveToEnd, machine, &CustomerMachine::rec_moveToEnd);
    connect(this, &Customer::sig_moveToCheckout, machine, &CustomerMachine::rec_moveToCheckout);

}

int Customer::watchDetect(MapCell* nextCell)
{
    //��Ұ���
    if (horizont == 3) {
        for (int i = -1; i < horizont - 1; i++) {
            for (int j = -1; j < horizont - 1; j++) {
                if (nextCell->x + i >= 0 && nextCell->x + i < map->mapCells.size() && nextCell->y + j >= 0 && nextCell->y + j < map->mapCells[0].size())
                    if (map->mapCells[nextCell->x + i][nextCell->y + j].type == CELL_SHELF) {
                        int shelfSn = storeManage->mapCellBelongsToWhichFacility(nextCell->x + i, nextCell->y + j);
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

        //�ߵ�nextCell�ῴ����Ե��һ������Ұ
        if (abs(nextCell->x - currentCell->x) + abs(nextCell->y - currentCell->y) == 1) {
            //�ӳ�3��

        }
        else {
            //5��
        }
        
    }
    else if (horizont == 4) {

    }
    else if (horizont == 5) {

    }

    return -1;
}

void Customer::moveToEnd(MapCell* end)
{
    if (path.size() == 0 || end == nullptr) {
        qDebug() << "Ѱ·��·��Ϊ�ջ�Ѱ·Ŀ�겻����";
        return;
    }

    bool isToCashier = false;

    if (end->type != CELL_CASHIER) {
        isToCashier = true;
    }

    int shelfSn = -1;
    currentCell = &map->mapCells[path[0].x][path[0].y];
    MapCell* nextCell = &map->mapCells[path[1].x][path[1].y];

    //����·������Ӧ���Ǹ�whileѭ��,·�ϲ���Ұ��ȥ������̨��ʱ�򲻲�
    while ((shelfSn = watchDetect(nextCell)) < 0 && !isToCashier && (nextCell->x != end->x && nextCell->y!= end->y)) {

        path.pop_front();
	    currentCell = nextCell;
		nextCell = &map->mapCells[path[1].x][path[1].y];
    }
    
    if (shelfSn) {
        list_shelf_detected.push_back(shelfSn);
        end->x = storeManage->shelfList[shelfSn]->list_mapcell_fetch[0].x;
		end->y = storeManage->shelfList[shelfSn]->list_mapcell_fetch[0].y;
        aimList.push_back(storeManage->shelfList[shelfSn]->list_mapcell_fetch[0]);

        //���ʽѰ·
        emit sig_moveToEnd();
    }
    else {
		//����һ�������յ�
        currentCell = nextCell;

        if (end->type == CELL_CASHIER) {
			//��������̨
			//���Ž��˶���
			//�����뿪����
		}
        else {
			//�������
			//���Ź��ﶯ��
			//�����뿪����
		}
	}
		
    
		
}

void Customer::moveToRandomShelf()
{
    if (!aimList.isEmpty()){
        //�Ѿ���Ŀ���ˣ����������������
        getPathInAimlist();
        moveToEnd(&aimList[0]);
        return;
    }
        

    MapCell* randMapCell;

    //�˿����Ѱ·��ȡĿ��
    if (list_shelf_detected.size() == storeManage->shelfList.size()) {
        //ȫ����Ѱ���ˣ�ȥ����
        int rand = std::rand() % storeManage->cashierList.size();
        randMapCell = &storeManage->cashierList[rand]->list_mapcell_fetch[0];
        aimList.push_back(storeManage->cashierList[rand]->list_mapcell_fetch[0]);
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


        aimList.push_back(map->mapCells[randMapCell->x + MapCell::circle_one[rand_pos].first][randMapCell->y + MapCell::circle_one[rand_pos].second]);
    }
    
    getPathInAimlist();
    

    //Ȼ���ߵ��յ�
    moveToEnd(randMapCell);
}

QState Customer::getCurrentState()
{  
    if(machine->configuration().values()[0])
        return qobject_cast<QState>(machine->configuration().values()[0]);
    else
        qDebug() << "���ܻ�õ�ǰ״̬";
}

QVector<MapCell> Customer::getPath()
{
    return path;
}

void Customer::CustomerTask::writePath()
{

}
