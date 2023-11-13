#include "StateClerkSlack.h"

StateClerkSlack::StateClerkSlack(QObject *parent)
	: AbstractClerkState(parent)
{
	m_slackTimer = new QTimer(this);
	m_slackTimer->setSingleShot(true);

	connect(m_slackTimer, &QTimer::timeout, this, &StateClerkSlack::toWork);
}

StateClerkSlack::~StateClerkSlack()
{}

void StateClerkSlack::setOwner(Clerk * clerk)
{
	owner = clerk;
	storeManage = owner->getStoreManage();

	int rd = 0;
	while ((rd = rand() % owner->getAIData()->slackRandom.second) < owner->getAIData()->slackRandom.first) {

	}
	m_slackTimer->start(rd);

}

void StateClerkSlack::toMove()
{
}

void StateClerkSlack::toWork()
{
	m_slackTimer->stop();
	emit slackToWork();
}

void StateClerkSlack::onInterruption() {
	
	toWork();
}