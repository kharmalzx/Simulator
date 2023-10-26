#include "CustomerMachine.h"

CustomerMachine::CustomerMachine(QObject *parent,Customer* owner)
	: QStateMachine(parent)
{
    this->owner = owner;
    initConnectToOwner();

    //�������е�״̬��״̬���������״̬
    //���룬�ƶ���������ˣ��뿪

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

    //�����ź����
    connect(enter, &QState::entered, this, &CustomerMachine::rec_fromStates_moveToRandomShelf);


    //��ʼ����״̬֮���ת��
    enter->addTransition(this, &CustomerMachine::sig_toStates_enterToMove, move);
    move->addTransition(this, &CustomerMachine::sig_toStates_moveToPurchase, purchase);
    move->addTransition(this, &CustomerMachine::sig_toStates_moveToMove, move); //Ѱ·��ʱ�򣬿����ٴ�Ѱ·��������Ұ�����
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
