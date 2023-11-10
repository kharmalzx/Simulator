#include "StateClerkLoad.h"

StateClerkLoad::StateClerkLoad(QObject *parent)
	: AbstractClerkState(parent)
{}

StateClerkLoad::~StateClerkLoad()
{}

void StateClerkLoad::setOwner(Clerk * clerk)
{
	owner = clerk;
}

void StateClerkLoad::toMove()
{
}
