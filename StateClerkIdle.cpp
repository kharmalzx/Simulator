#include "StateClerkIdle.h"

StateClerkIdle::StateClerkIdle(QObject *parent)
	: AbstractClerkState(parent)
{}

StateClerkIdle::~StateClerkIdle()
{}

void StateClerkIdle::setOwner(Clerk * clerk)
{
}

void StateClerkIdle::toMove()
{
}
