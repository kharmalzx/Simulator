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
	//�����ﻹ��Ҫ�жϻ��ܴ���
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
			//���ȡ����
			owner->fetchCommodityOneTick(owner->findCommoditySn);
		}
		else {
			//˵����ʩ��ǰ�Ĵ�������������ô�ȴ�
		}
	}
	
		

}

void StateFetch::OnInterruption()
{
}
