#include "StateFetch.h"

StateFetch::StateFetch(QObject *parent): AbstractCustomerState(parent)
{
	fetchTickTimer = new QTimer(this);

	connect(fetchTickTimer, &QTimer::timeout, this, &StateFetch::onFetchTimerOut);


}

StateFetch::~StateFetch()
{
	

}

void StateFetch::setOwner(Customer* owner)
{
	this->owner = owner;
	this->storeManage = owner->storeManage;

	targetFacility = storeManage->getFaciPtr(owner->queueInfo.facilitySn);
	tick = targetFacility->service_tick / owner->AIData.coefficient_fetch;
	fetchTickTimer->setInterval(tick);
	
}

void StateFetch::onEntry(QEvent* event)
{
	//在这里还需要判断货架储量
	fetchTickTimer->start();
}

void StateFetch::ToMove()
{
	owner->findCommoditySn = 0;
	emit fetchToMove();
}

void StateFetch::onFetchTimerOut() {
	
	CommodityNeed* cn = owner->getCommodityNeed(owner->findCommoditySn);

	if (cn != nullptr) {
		int fetchCount = cn->num_require >= cn->fetchCount_pertick ? cn->fetchCount_pertick : cn->num_require;
		if (storeManage->fetchOneOnFacility(owner->queueInfo.facilitySn, fetchCount)) {
			//如果取到了
			owner->fetchCommodityOneTick(owner->findCommoditySn);
		}
		else {
			//说明设施当前的储货量不够，那么等待
		}
	}
	
		

}

void StateFetch::OnInterruption()
{
}
