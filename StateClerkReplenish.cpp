#include "StateClerkReplenish.h"

StateClerkReplenish::StateClerkReplenish(QObject *parent)
	: AbstractClerkState(parent)
{}

StateClerkReplenish::~StateClerkReplenish()
{}

void StateClerkReplenish::setOwner(Clerk * clerk)
{
	owner = clerk;
}

void StateClerkReplenish::toMove()
{
}
