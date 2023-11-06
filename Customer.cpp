#include "Customer.h"

Customer::Customer(QObject* parent)
{
	//初始化状态机
    machine = new CustomerMachine(this,this);
    
    findCommoditySn = 0;
}



void Customer::animationMoveTo(MapCell* next)
{
    if (abs(next->x() - currentCell->x()) + abs(next->y() - currentCell->y()) > 2) {
        qDebug() << "顾客" << AIData.id << "移动距离过大，点位" << currentCell->x() << "," << currentCell->y();
        return;
    }
		

    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
	QPropertyAnimation* animation1 = new QPropertyAnimation(this, "pos");
	animation1->setDuration(1000);
	animation1->setStartValue(QPoint(currentCell->x(), currentCell->y()));
	animation1->setEndValue(QPoint(next->x(), next->y()));
	group->addAnimation(animation1);
	group->start(QAbstractAnimation::DeleteWhenStopped);

    currentCell = next;
}

void Customer::check_if_queueStateChange()
{

    emit checkQueueStateChange();

}

QState Customer::getCurrentState()
{  
    if(machine->configuration().values()[0])
        return qobject_cast<QState>(machine->configuration().values()[0]);
    else
        qDebug() << "不能获得当前状态";
}

void Customer::fetchCommodityOneTick(const int& commoditySn)
{
    CommodityNeed* c = getCommodityNeed(commoditySn);

    if (c != nullptr) {
        if (c->num_require - c->fetchCount_pertick <= 0)
            c->num_require = 0;
        else c->num_require = c->num_require - c->fetchCount_pertick;
    }
    else {
        qDebug() << "找不到顾客" << AIData.id << "想要的商品sn" << commoditySn;
    }
    
}

CommodityNeed* Customer::getCommodityNeed(const int& commoditySn)
{
    for (int i = 0; i < AIData.list_commodity_needs.size(); i++) {
        if (AIData.list_commodity_needs[i].commoditySn == commoditySn)
            return &AIData.list_commodity_needs[i];
    }

    return nullptr;
}
