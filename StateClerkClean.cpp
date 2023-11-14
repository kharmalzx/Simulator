#include "StateClerkClean.h"

StateClerkClean::StateClerkClean(QObject *parent)
	: AbstractClerkState(parent)
{}

StateClerkClean::~StateClerkClean()
{}

void StateClerkClean::setOwner(Clerk * owner)
{
	this->owner = owner;
}

void StateClerkClean::toMove()
{
	emit cleanToMove();
}
