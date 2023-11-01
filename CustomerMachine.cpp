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



    addState(enter);
    addState(move);
    addState(queue);
    addState(fetch);

    setInitialState(enter);

    //�����ź����


    //��ʼ����״̬֮���ת��
    enter->addTransition(enter, &StateEnter::enterTomove, move);
    move->addTransition(move, &StateMove::moveToQueue,queue);
    queue->addTransition(queue, &StateQueue::QueueToMove, move);
    queue->addTransition(queue, &StateQueue::QueueToFetch, fetch);
    fetch->addTransition(fetch, &StateFetch::fetchToMove, move);
}



CustomerMachine::~CustomerMachine()
{}