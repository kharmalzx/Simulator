#include "StateClerkIdle.h"

StateClerkIdle::StateClerkIdle(QObject *parent)
	: AbstractClerkState(parent)
{}

StateClerkIdle::~StateClerkIdle()
{}

void StateClerkIdle::setOwner(Clerk * clerk)
{
	owner = clerk;

}

void StateClerkIdle::onEntry(QEvent* e)
{
	owner->setWorkAction(ClerkAction::IDLE);
}

void StateClerkIdle::onInterruption() {

	toMove();
	toService();
}

void StateClerkIdle::toMove()
{
	emit idleToMove();
}

void StateClerkIdle::toService()
{
	emit idleToService();
}
