#include "CustomerMachine.h"

CustomerMachine::CustomerMachine(QObject *parent,Customer* owner)
	: QStateMachine(parent)
{
    this->owner = owner;

    //�������е�״̬��״̬���������״̬
    //���룬�ƶ���������ˣ��뿪

    enter = new StateEnter(this);
    move = new StateMove(this);
    queue = new StateQueue(this);
    fetch = new StateFetch(this);
    checkout = new StateCheckout(this);
    exit = new StateExit(this);


    addState(enter);
    addState(move);
    addState(queue);
    addState(fetch);
    addState(checkout);
    addState(exit);
    

    setInitialState(enter);

    //�����ź����


    //��ʼ����״̬֮���ת��
    enter->addTransition(enter, &StateEnter::enterTomove, move);
    move->addTransition(move, &StateMove::moveToQueue,queue);
    queue->addTransition(queue, &StateQueue::queueToMove, move);
    queue->addTransition(queue, &StateQueue::queueToFetch, fetch);
    queue->addTransition(queue,&StateQueue::queueToCheckout, checkout);
    fetch->addTransition(fetch, &StateFetch::fetchToMove, move);
    checkout->addTransition(checkout, &StateCheckout::checkoutToMove, move);
    move->addTransition(move, &StateMove::moveToExit, exit);
}



CustomerMachine::~CustomerMachine()
{}

void CustomerMachine::setOwner(Customer * owner)
{
    this->owner = owner;
}
