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
	cur_count = max_size;
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
	QMutexLocker locker(&serviceMutex);
	cur_count -= fetchCount;
}



Cashier::Cashier()
{
}

Cashier::~Cashier()
{
}
