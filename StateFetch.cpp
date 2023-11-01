#include "StateFetch.h"

StateFetch::StateFetch(QObject *parent): AbstractCustomerState(parent)
{
	fetchTimer = new QTimer(this);

	connect(fetchTimer, &QTimer::timeout, this, &StateFetch::onFetchTimerOut);


}

StateFetch::~StateFetch()
{
	

}

void StateFetch::setOwner(Customer* owner)
{
	this->owner = owner;
	this->storeManage = owner->storeManage;

	tick = storeManage->getFaciPtr(owner->queueInfo.facilitySn)->service_tick / owner->AIData.coefficient_fetch;
	fetchTimer->setInterval(tick);
}

void StateFetch::onEntry(QEvent* event)
{
	fetchTimer->start();
}

void StateFetch::ToMove()
{
	emit fetchToMove();
}

void StateFetch::onFetchTimerOut() {
	
	

}

void StateFetch::OnInterruption()
{
}
