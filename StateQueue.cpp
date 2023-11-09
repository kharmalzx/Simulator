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

void StateQueue::toMove()
{
	clearQueueInfoWhenLeave();

	owner->findCommoditySn = 0;
	emit queueToMove();
}

void StateQueue::toCheckout()
{
	clearQueueInfoWhenFaci();

	emit queueToCheckout();
}

void StateQueue::clearQueueInfoWhenLeave()
{
	owner->queueInfo.isQueue = false;
	owner->queueInfo.isInQueue1 = false;
	owner->queueInfo.facilitySn = 0;
	owner->queueInfo.fetchPointOrd = 0;
}

void StateQueue::clearQueueInfoWhenFaci()
{
	owner->queueInfo.isQueue = false;
	owner->queueInfo.isInQueue1 = false;
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
	toMove();
}

void StateQueue::checkQueueStateChange()
{
	int population = getFacilityPopulation();
	
	if (storeManage->getQueueLength(owner->queueInfo.facilitySn, owner->queueInfo.fetchPointOrd) == 1) {
		toFetch();
		return;
	}


	if (owner->AIData.num_tolerance >= population)
	{
		timer_queue2->stop();
		
	}

}


void StateQueue::toFetch()
{
	owner->queueInfo.isQueue = false;
	owner->queueInfo.isInQueue1 = false;

	emit queueToFetch();
}
