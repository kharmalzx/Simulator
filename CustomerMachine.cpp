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


    //��ʼ����״̬֮���ת��
    enter->addTransition(this, &CustomerMachine::enterToMove, move);
    move->addTransition(this, &CustomerMachine::moveToPurchase, purchase);
    move->addTransition(this, &CustomerMachine::moveToMove, move); //Ѱ·��ʱ�򣬿����ٴ�Ѱ·��������Ұ�����
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
    //���͸�owner
    emit sig_toOwner_moveToRandomShelf();
}

void CustomerMachine::initConnectToOwner()
{
    connect(this,&CustomerMachine::sig_toOwner_moveToRandomShelf,owner,&Customer::moveToRandomShelf);

}
