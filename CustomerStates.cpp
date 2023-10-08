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

void StatePurchase::addState(QState* targetState)
{
	auto transition = new QSignalTransition(this, SIGNAL(transitionToState(QEvent*)));
}
