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

	m_slackTimer->setInterval(Clerk::slackTime);

}

void StateClerkSlack::onEntry(QEvent* event)
{
	Q_UNUSED(event);
	if (owner != nullptr)
		m_slackTimer->start();
	else
		qDebug() << "StateClerkSlack's owner is nullptr";
}

void StateClerkSlack::toMove()
{
}

void StateClerkSlack::toWork()
{
	if(m_slackTimer->isActive())
		m_slackTimer->stop();
	emit slackToWork();
}

void StateClerkSlack::onInterruption() {
	
	toWork();
}