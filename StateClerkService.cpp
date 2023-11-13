#include "StateClerkService.h"

StateClerkService::StateClerkService(QObject *parent)
	: AbstractClerkState(parent)
{}

StateClerkService::~StateClerkService()
{}

void StateClerkService::setOwner(Clerk * clerk)
{
	owner = clerk;

	
}

void StateClerkService::toMove()
{
}
