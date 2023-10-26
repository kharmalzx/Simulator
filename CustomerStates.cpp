#include "CustomerStates.h"

StatePurchase::StatePurchase(QState* parent, CustomerMachine* machine)
{
	state = STATE_PURCHASE;
	qDebug() << "StatePurchase::onPurchase";
	
	//先这么写着，后面要用再调整
	connect(this, &StatePurchase::moveToPurchase, machine, &CustomerMachine::rec_fromStates_moveToPurchase);
}

void StatePurchase::onEntry(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StatePurchase::onEntry";
	
	//状态转换成功后发送信号
	emit moveToPurchase();
}

void StatePurchase::onExit(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StatePurchase::onExit";
}


StateMove::StateMove(QState* parent, CustomerMachine* machine)
{
	state = STATE_MOVE;
	qDebug() << "StateMove::onMove";

}

void StateMove::onEntry(QEvent* e)
{
	Q_UNUSED(e);

	qDebug() << "StateMove::onEntry";

}

void StateMove::onExit(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateMove::onExit";

}

void StateQueue::onEntry(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateQueue::onEntry";
}

void StateQueue::onExit(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateQueue::onExit";

}

void StateEnter::onEntry(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateEnter::onEntry";

}

void StateEnter::onExit(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateEnter::onExit";
}

void StateExit::onEntry(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateExit::onEntry";
}

void StateExit::onExit(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateExit::onExit";
}

void StateCheckout::onEntry(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateCheckout::onEntry";
}

void StateCheckout::onExit(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateCheck::onExit";
}


