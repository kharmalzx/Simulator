#include "Shelf.h"

void Facility::updateQueue(const int& fetchPoint, const int& customerId, MapCell* c)
{
	//如果新开取货口，和下面的做出区别
	if (list_queue.size() < fetchPoint + 1) {
		QueueCellInfo info;
		info.cellAt = c;
		info.customerId = customerId;
		QVector<QueueCellInfo> q;
		q.push_back(info);
		list_queue.push_back(q);
		return;
	}

	//离队和进队都在一个函数里做
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
