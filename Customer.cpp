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
}

void Customer::initStateMachine()
{
    //�������е�״̬��״̬���������״̬
    //���룬�ƶ���������ˣ��뿪
    c_machine = new QStateMachine(this);
    StateEnter* enter = new StateEnter(c_machine);
    StateMove* move = new StateMove(c_machine,this);
    StatePurchase* purchase = new StatePurchase(c_machine);
    StateCheckout* checkout = new StateCheckout(c_machine);
    StateExit* exit = new StateExit(c_machine);
    StateSlack* slack = new StateSlack(c_machine);


    c_machine->addState(enter);
    c_machine->addState(move);
    c_machine->addState(purchase);
    c_machine->addState(checkout);
    c_machine->addState(exit);

    c_machine->setInitialState(enter);
    currentState = enter;
    

    //�����ź����
    

    //��ʼ����״̬֮���ת��
    enter->addTransition(this,&Customer::enter,move);
    move->addTransition(this, &Customer::purchaseStarted, purchase);
    purchase->addTransition(this, &Customer::purchaseToMove, move);
    move->addTransition(this, &Customer::checkoutStart, checkout);
    checkout->addTransition(this, &Customer::checkoutFinished, move);
    move->addTransition(this, &Customer::exit, exit);

}

void Customer::movetoEnd()
{

}

void Customer::moveToRandomShelf()
{
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
    if (randMapCell->type == CELL_CASHIER) {
        emit moveToCheckout();
        movetoEnd();
    }
    else if (randMapCell->type == CELL_SHELF) {
        movetoEnd();
    }
}

QVector<MapCell> Customer::getPath()
{
    return path;
}

void Customer::CustomerTask::writePath()
{

}
