#include "Shelf.h"

void Facility::updateQueue(const int& fetchPoint, const int& customerId, MapCell* c)
{
	//如果新开取货口不在这里处理
	if (list_queue.size() < fetchPoint) {
		qDebug() << "没有在升级时扩大取货口位置";
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
	cur_population++;

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
