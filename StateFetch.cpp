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
		//�ȴ�����֪ͨ
	}
	
}

void StateFetch::ToMove()
{
	owner->findCommoditySn = 0;

	//�˳�����

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

		//�����Ƿ����ȡ��
		if (c->num_require > 0) {
			canFetchCommodity();
		}	
		else {
			//ȡ����ɣ��˳�����
			ToMove();
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
		int fetchCount = cn->num_require >= cn->fetchCount_pertick ? cn->fetchCount_pertick : cn->num_require;
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
