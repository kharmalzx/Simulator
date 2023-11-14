#include "StateClerkWorking.h"

StateClerkWorking::StateClerkWorking(QObject *parent)
	: AbstractClerkState(parent)
{
	m_workingTimer = new QTimer(this);
	m_workingTimer->setSingleShot(true);

	m_slackTimer = new QTimer(this);

	connect(m_workingTimer, &QTimer::timeout, this, &StateClerkWorking::toRest);
	connect(m_slackTimer, &QTimer::timeout, this, &StateClerkWorking::toSlack);
	
}

StateClerkWorking::~StateClerkWorking()
{}

void StateClerkWorking::setOwner(Clerk * owner)
{
	this->owner = owner;
	storeManage = owner->getStoreManage();
	
	m_workingTimer->setInterval(owner->getAIData()->stamina);

}

void StateClerkWorking::onEntry(QEvent*)
{
	if (owner != nullptr) {
		int rd = 0;
		while ((rd = rand() % owner->getAIData()->slackRandom.second) < owner->getAIData()->slackRandom.first) {}
		m_slackTimer->start(rd);
	}	
	else
		qDebug() << "StateClerkWorking's owner is nullptr";
}

void StateClerkWorking::onExit(QEvent*)
{
	m_workingTimer->stop();
	m_slackTimer->stop();

	owner->setWillRest(false);
	owner->setWillSlack(false);
	owner->setWorkCell(owner->locAt());
}

bool StateClerkWorking::checkIfTimeToRest()
{
	QList<AbstractClerkState*> states = findChildren<AbstractClerkState*>();
	foreach (QState* s, states)
	{
		if (s->active()) {
			if(s->objectName() == "StateClerkMove" || s->objectName() == "StateClerkIdle") {
				return true;
			}
		}
	}
	return false;
}

bool StateClerkWorking::checkIfTimeToSlack()
{
	QList<AbstractClerkState*> states = findChildren<AbstractClerkState*>();
	foreach(QState* s, states)
	{
		if (s->active()) {
			if (s->objectName() == "StateClerkIdle") {
				return true;
			}
		}
	}
	return false;
}

void StateClerkWorking::toMove()
{
}

void StateClerkWorking::toSlack()
{
	owner->setWorkAction(ClerkAction::SLACK);
	if (checkIfTimeToSlack()) {
		emit workingToSlack();
	}
	else {
		owner->setWillSlack(true);
	}
	
}

void StateClerkWorking::toRest()
{
	owner->setWorkAction(ClerkAction::REST);
	if (checkIfTimeToRest()) {
		emit workingToRest();
	}
	else {
		owner->setWillRest(true);
	}
	
}
