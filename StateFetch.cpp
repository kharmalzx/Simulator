#include "StateFetch.h"

StateFetch::StateFetch(QObject *parent): AbstractCustomerState(parent)
{
	fetchTickTimer = new QTimer(this);

	connect(fetchTickTimer, &QTimer::timeout, this, &StateFetch::onFetchTimerOut);
	

}

StateFetch::~StateFetch()
{}

void StateFetch::setOwner(Customer* owner)
{
	this->owner = owner;
	this->storeManage = owner->storeManage;

	targetFacility = storeManage->getFaciPtr(owner->queueInfo.facilitySn);
	tick = targetFacility->service_tick * owner->AIData.coefficient_fetch / 1000;
	fetchTickTimer->setSingleShot(true);
	fetchTickTimer->setInterval(tick);
	
	connect(owner, &Customer::checkFetch, this, &StateFetch::onCheckReplenishment);
}

void StateFetch::onEntry(QEvent* event)
{
	if (canFetchCommodity()) {
		fetchTickTimer->start();
	}	
}

void StateFetch::toMove()
{
	owner->findCommoditySn = 0;

	//�˳�����
	storeManage->requestQuitQueue(owner);
	emit fetchToMove();
}

void StateFetch::onFetchTimerOut() {

	fetchTickTimer->stop();
	fetchCommodity();
}

void StateFetch::onInterruption()
{
}

void StateFetch::onCheckReplenishment()
{
	if (canFetchCommodity())
		fetchTickTimer->start();
}

void StateFetch::fetchCommodity()
{
	CommodityNeed* c = owner->getCommodityNeed(owner->findCommoditySn);

	if (c != nullptr) {
		if (c->num_remain - c->fetchCount_pertick <= 0) {
			c->num_remain = 0;
			c->num_fetched += c->num_remain;
		}	
		else { 
			c->num_remain = c->num_remain - c->fetchCount_pertick;
			c->num_fetched += c->fetchCount_pertick;
		}
		storeManage->realFetchOnFacility(owner->queueInfo.facilitySn, c->fetchCount_pertick);

		//�����Ƿ����ȡ��
		if (c->num_remain > 0) {
			if(canFetchCommodity())
				fetchTickTimer->start();
		}	
		else {
			//ȡ����ɣ��˳�����
			toMove();
		}
	}
	else {
		qDebug() << "�Ҳ����˿�" << owner->AIData.id << "��Ҫ����Ʒsn" << owner->findCommoditySn;
	}
}

bool StateFetch::canFetchCommodity()
{
	CommodityNeed* cn = owner->getCommodityNeed(owner->findCommoditySn);

	if (cn != nullptr) {
		int fetchCount = cn->num_remain >= cn->fetchCount_pertick ? cn->fetchCount_pertick : cn->num_remain;
		if (storeManage->canFetchOnFacility(owner->queueInfo.facilitySn, fetchCount)) {
			//����ܹ�ȡ������ô�Ѿ�������������ʼ��ʱ������û�û��ܼ��ٴ���
			return true;

		}
		else {
			//˵����ʩ��ǰ�Ĵ�������������ô�ȴ�
			return false;
		}
	}
	else {
		qDebug() << "�Ҳ����˿�" << owner->AIData.id << "��Ҫ����Ʒsn" << owner->findCommoditySn;
	}
}
