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
	sn = 1;

}

Shelf::~Shelf()
{
}

bool Shelf::fetchOneCommodity(const int& fetchCount)
{
	QMutexLocker locker(&serviceMutex);

	if (cur_count < fetchCount)return false;
	
	cur_count = cur_count - fetchCount;
	return true;
}



Cashier::Cashier()
{
}

Cashier::~Cashier()
{
}
