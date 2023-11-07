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
	tick = targetFacility->service_tick * owner->AIData.coefficient_fetch / 1000;
	fetchTickTimer->setSingleShot(true);
	fetchTickTimer->setInterval(tick);
	
}

void StateFetch::onEntry(QEvent* event)
{
	if (canFetchCommodity()) {
		fetchTickTimer->start();
	}
	else {
		//等待货架通知
	}
	
}

void StateFetch::ToMove()
{
	owner->findCommoditySn = 0;

	//退出队伍

	emit fetchToMove();
}

void StateFetch::onFetchTimerOut() {

	fetchTickTimer->stop();
	fetchCommodity();
}

void StateFetch::OnInterruption()
{
}

void StateFetch::fetchCommodity()
{
	CommodityNeed* c = owner->getCommodityNeed(owner->findCommoditySn);

	if (c != nullptr) {
		if (c->num_require - c->fetchCount_pertick <= 0)
			c->num_require = 0;
		else c->num_require = c->num_require - c->fetchCount_pertick;
		storeManage->realFetchOnFacility(owner->queueInfo.facilitySn, c->fetchCount_pertick);

		//决定是否继续取货
		if (c->num_require > 0) {
			canFetchCommodity();
		}	
		else {
			//取货完成，退出队伍
			ToMove();
		}
	}
	else {
		qDebug() << "找不到顾客" << owner->AIData.id << "想要的商品sn" << owner->findCommoditySn;
	}
}

bool StateFetch::canFetchCommodity()
{
	CommodityNeed* cn = owner->getCommodityNeed(owner->findCommoditySn);

	if (cn != nullptr) {
		int fetchCount = cn->num_require >= cn->fetchCount_pertick ? cn->fetchCount_pertick : cn->num_require;
		if (storeManage->canFetchOnFacility(owner->queueInfo.facilitySn, fetchCount)) {
			//如果能够取货，那么已经锁定数量，开始计时，但还没让货架减少储量
			return true;

		}
		else {
			//说明设施当前的储货量不够，那么等待
			return false;
		}
	}
	else {
		qDebug() << "找不到顾客" << owner->AIData.id << "想要的商品sn" << owner->findCommoditySn;
	}
}
