#include "StateClerkService.h"

StateClerkService::StateClerkService(QObject *parent)
	: AbstractClerkState(parent)
{
	m_serviceTimer = new QTimer(this);
	m_serviceTimer->setSingleShot(true);

	connect(m_serviceTimer, &QTimer::timeout, this, &StateClerkService::onServiceFinished);
}

StateClerkService::~StateClerkService()
{}

void StateClerkService::setOwner(Clerk * clerk)
{
	owner = clerk;
	m_serviceTimer->setInterval(owner->getAIData()->serveSpeed);
	
}

void StateClerkService::onEntry(QEvent* event)
{
	owner->setWorkAction(ClerkAction::SERVICE);
	owner->setWorkCell(owner->locAt());
	service();
}

void StateClerkService::onExit(QEvent* event)
{
	m_serviceTimer->stop();
}

void StateClerkService::onServiceFinished()
{
	if (storeManage->getQueueLength(owner->getWorkingFacility()->sn, 0) > 0) {
		service();
	}
	else {
		toIdle();
	}
}

void StateClerkService::service()
{
	m_serviceTimer->start();
	//²¥¶¯»­

}

void StateClerkService::toMove()
{
	emit serviceToMove();
}

void StateClerkService::toIdle()
{
	emit serviceToIdle();
}
