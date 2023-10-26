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
    connect(enter, &QState::entered, this, &CustomerMachine::rec_fromStates_moveToRandomShelf);


    //初始化各状态之间的转换
    enter->addTransition(this, &CustomerMachine::sig_toStates_enterToMove, move);
    move->addTransition(this, &CustomerMachine::sig_toStates_moveToPurchase, purchase);
    move->addTransition(this, &CustomerMachine::sig_toStates_moveToMove, move); //寻路的时候，可能再次寻路，可能视野被打断
    purchase->addTransition(this, &CustomerMachine::sig_toStates_purchaseToMove, move);
    move->addTransition(this, &CustomerMachine::sig_toStates_moveToCheckout, checkout);
    checkout->addTransition(this, &CustomerMachine::sig_toStates_checkoutToMove, move);
    move->addTransition(this, &CustomerMachine::sig_toStates_moveToExit, exit);

}



CustomerMachine::~CustomerMachine()
{}


void CustomerMachine::rec_fromOwner_moveToEnd()
{
    emit sig_toStates_moveToMove();
}

void CustomerMachine::rec_fromOwner_moveToCheckout()
{
    emit sig_toStates_moveToCheckout();
}

void CustomerMachine::rec_fromOwner_moveToPurchase()
{
    emit sig_toStates_moveToPurchase();
}

void CustomerMachine::rec_fromStates_moveToRandomShelf()
{
    emit sig_toOwner_moveToRandomShelf();
}

void CustomerMachine::rec_fromStates_moveToPurchase()
{
	emit sig_toOwner_moveToPurchase();

}
