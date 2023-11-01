#include "StateQueue.h"

StateQueue::StateQueue(QObject* parent): AbstractCustomerState(parent)
{
	timer_queue2 = new QTimer(this);
	timer_queue2->setSingleShot(true);
	timer_queue2->setInterval(owner->AIData.t_wait_patience);
	connect(timer_queue2, &QTimer::timeout, this, &StateQueue::onQueue2Timeout);
	connect(owner,&Customer::checkQueueStateChange,this,&StateQueue::checkQueueStateChange);
}

StateQueue::~StateQueue()
{}

void StateQueue::onEntry(QEvent* event)
{
	timer_queue2->start();

}

void StateQueue::ToMove()
{
	emit QueueToMove();
}

void StateQueue::setOwner(Customer* owner)
{
	this->owner = owner;
	
}

int StateQueue::getFacilityPopulation()
{
	return storeManage->getFacilityPopulation(owner->queueInfo.facilitySn);
}

void StateQueue::onQueue2Timeout()
{
	ToMove();
}

void StateQueue::checkQueueStateChange()
{
	int population = getFacilityPopulation();
	
	if (storeManage->getQueueLength(owner->queueInfo.facilitySn, owner->queueInfo.fetchPoint) == 1) {
		ToFetch();
		return;
	}


	if (owner->AIData.num_tolerance >= population)
	{
		timer_queue2->stop();
		
	}

}


void StateQueue::ToFetch()
{
	emit QueueToFetch();
}
