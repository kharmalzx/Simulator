#include "Shelf.h"

void Facility::updateQueue(const int& fetchPoint, const int& customerId, MapCell* c)
{
	//����¿�ȡ���ڣ����������������
	if (list_queue.size() < fetchPoint + 1) {
		QueueCellInfo info;
		info.cellAt = c;
		info.customerId = customerId;
		QVector<QueueCellInfo> q;
		q.push_back(info);
		list_queue.push_back(q);
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

}

Shelf::Shelf()
{
	sn = 1;

}

Shelf::~Shelf()
{
}



Cashier::Cashier()
{
}

Cashier::~Cashier()
{
}
