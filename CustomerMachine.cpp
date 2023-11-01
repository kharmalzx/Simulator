#include "CustomerMachine.h"

CustomerMachine::CustomerMachine(QObject *parent,Customer* owner)
	: QStateMachine(parent)
{
    this->owner = owner;

    //声明所有的状态，状态机添加所有状态
    //进入，移动，购物，结账，离开

    enter = new StateEnter(this);
    move = new StateMove(this);
    queue = new StateQueue(this);



    addState(enter);
    addState(move);
    addState(queue);
    addState(fetch);

    setInitialState(enter);

    //连接信号与槽


    //初始化各状态之间的转换
    enter->addTransition(enter, &StateEnter::enterTomove, move);
    move->addTransition(move, &StateMove::moveToQueue,queue);
    queue->addTransition(queue, &StateQueue::QueueToMove, move);
    queue->addTransition(queue, &StateQueue::QueueToFetch, fetch);
    fetch->addTransition(fetch, &StateFetch::fetchToMove, move);
}



CustomerMachine::~CustomerMachine()
{}