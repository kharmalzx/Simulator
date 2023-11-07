#include "StateEnter.h"

StateEnter::StateEnter(QObject *parent): AbstractCustomerState(parent)
{}

StateEnter::~StateEnter()
{}

void StateEnter::toMove()
{
}

void StateEnter::setOwner(Customer* owner)
{
	this->owner = owner;
}

void StateEnter::onInterruption()
{
}
