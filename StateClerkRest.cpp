#include "StateClerkRest.h"

StateClerkRest::StateClerkRest(QObject *parent)
	: AbstractClerkState(parent)
{}

StateClerkRest::~StateClerkRest()
{}

void StateClerkRest::setOwner(Clerk * clerk)
{
	owner = clerk;
}

void StateClerkRest::toMove()
{
}
