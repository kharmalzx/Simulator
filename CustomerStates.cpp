#include "CustomerStates.h"

void StatePurchase::onEntry(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StatePurchase::onEntry";
	

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
	connect(this, &QState::entered, machine, &CustomerMachine::rec_moveToRandomShelf);

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

void StateSlack::onEntry(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateSlack::onEntry";
}

void StateSlack::onExit(QEvent* e)
{
	Q_UNUSED(e);
	qDebug() << "StateSlack::onExit";
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


