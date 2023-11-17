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
	//ÿx���1������
	if (owner->staminaChange(-1))
	{
		//��������������ͽ���rest״̬
		toRest();
		return;
	}
	


	//���ǰ��û�£��ͽ���idle״̬
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
