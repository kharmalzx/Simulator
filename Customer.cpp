#include "Customer.h"

Customer::Customer(QObject* parent)
{
	//��ʼ��״̬��
    machine = new CustomerMachine(this,this);
    
}



void Customer::animationMoveTo(MapCell* next)
{
    if (abs(next->x() - currentCell->x()) + abs(next->y() - currentCell->y()) > 2) {
        qDebug() << "�˿�" << AIData.id << "�ƶ�������󣬵�λ" << currentCell->x() << "," << currentCell->y();
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

void Customer::check_if_queue2to1()
{

    emit checkQueueStateChange();

}

QState Customer::getCurrentState()
{  
    if(machine->configuration().values()[0])
        return qobject_cast<QState>(machine->configuration().values()[0]);
    else
        qDebug() << "���ܻ�õ�ǰ״̬";
}