#include "CustomerMachine.h"

CustomerMachine::CustomerMachine(QObject *parent,Customer* owner)
	: QStateMachine(parent)
{
    this->owner = owner;
    initConnectToOwner();

    //声明所有的状态，状态机添加所有状态
    //进入，移动，购物，结账，离开

    enter = new StateEnter(this);
    move = new StateMove(this,this);
    purchase = new StatePurchase(this);
    checkout = new StateCheckout(this);
    exit = new StateExit(this);
    slack = new StateSlack(this);

    addState(enter);
    addState(move);
    addState(purchase);
    addState(checkout);
    addState(exit);
    addState(slack);

    setInitialState(enter);

    //连接信号与槽


    //初始化各状态之间的转换
    enter->addTransition(this, &CustomerMachine::enterToMove, move);
    move->addTransition(this, &CustomerMachine::moveToPurchase, purchase);
    move->addTransition(this, &CustomerMachine::moveToMove, move); //寻路的时候，可能再次寻路，可能视野被打断
    purchase->addTransition(this, &CustomerMachine::purchaseToMove, move);
    move->addTransition(this, &CustomerMachine::moveToCheckout, checkout);
    checkout->addTransition(this, &CustomerMachine::checkoutToMove, move);
    move->addTransition(this, &CustomerMachine::moveToExit, exit);

}



CustomerMachine::~CustomerMachine()
{}


void CustomerMachine::rec_moveToEnd()
{
    emit moveToMove();
}

void CustomerMachine::rec_moveToCheckout()
{
    emit moveToCheckout();
}

void CustomerMachine::rec_moveToRandomShelf()
{
    //发送给owner
    emit sig_toOwner_moveToRandomShelf();
}

void CustomerMachine::initConnectToOwner()
{
    connect(this,&CustomerMachine::sig_toOwner_moveToRandomShelf,owner,&Customer::moveToRandomShelf);

}
