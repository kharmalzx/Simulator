#include "Shelf.h"

void Facility::updateQueue(const int& fetchPoint, const int& customerId, MapCell* c)
{
	//����¿�ȡ���ڲ������ﴦ��
	if (list_queue.size() < fetchPoint) {
		qDebug() << "û��������ʱ����ȡ����λ��";
		return;
	}

	//��Ӻͽ��Ӷ���һ����������
	for (int i = 0; i < list_queue[fetchPoint].size(); i++) {
		if (list_queue[fetchPoint][i].customerId == customerId) {
			list_queue[fetchPoint].remove(i);
			return;
		}
	}

	QueueCellInfo info;
	info.cellAt = c;
	info.customerId = customerId;
	list_queue[fetchPoint].push_back(info);
	cur_population++;

}

Shelf::Shelf()
{
	cur_count = maxStorage;
	expected_count = cur_count;
	sn = 1;

}

Shelf::~Shelf()
{
}

bool Shelf::canFetchCommodity(const int& fetchCount)
{
	QMutexLocker locker(&expectedMutex);

	if (expected_count < fetchCount)return false;
	else
	{
		expected_count -= fetchCount;
		return true;
	}
	
}

void Shelf::realFetchCommodity(const int& fetchCount)
{
	QMutexLocker locker(&commodityMutex);
	cur_count -= fetchCount;
}

void Shelf::replenishCommodity()
{
	QMutexLocker locker(&commodityMutex);
	QMutexLocker locker2(&expectedMutex);

	cur_count = maxStorage;
	expected_count = maxStorage;
}



Cashier::Cashier()
{
}

Cashier::~Cashier()
{
}
