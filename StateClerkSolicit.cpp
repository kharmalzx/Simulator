#include "StateClerkSolicit.h"

StateClerkSolicit::StateClerkSolicit(QObject *parent)
	: AbstractClerkState(parent)
{
	m_solicitTimer = new QTimer(this);

	connect(m_solicitTimer, SIGNAL(timeout()), this, SLOT(onSolicitTimerTimeout()));
}

StateClerkSolicit::~StateClerkSolicit()
{}

void StateClerkSolicit::setOwner(Clerk * clerk)
{
	owner = clerk;
	storeManage = owner->getStoreManage();
	storeSettings = storeManage->getStoreSettingsPtr();

	m_solicitTimer->setInterval(storeSettings->solicitStamina());
}

void StateClerkSolicit::onEntry(QEvent* event)
{
	storeManage->changeSolicitCount(1);
	m_solicitTimer->start();

}

void StateClerkSolicit::onExit(QEvent* event)
{
	if(m_solicitTimer->isActive())
		m_solicitTimer->stop();
}

void StateClerkSolicit::onInterruption() {

	toMove();

}

void StateClerkSolicit::onSolicitTimerTimeout()
{
	//每x秒掉1点体力
	if (owner->staminaChange(-1))
	{
		//如果体力不够，就进入rest状态
		toRest();
		return;
	}
	


	//如果前面没事，就进入idle状态
	toIdle();
}

void StateClerkSolicit::toMove()
{
	emit solicitToMove();
}

void StateClerkSolicit::toIdle()
{
	emit solicitToIdle();
}

void StateClerkSolicit::toRest()
{
	emit solicitToRest();
}
