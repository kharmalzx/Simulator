#include "StateClerkMove.h"

StateClerkMove::StateClerkMove(QObject *parent)
	: AbstractClerkState(parent)
{}

StateClerkMove::~StateClerkMove()
{}

void StateClerkMove::setOwner(Clerk * clerk)
{
	m_owner = clerk;

}

void StateClerkMove::toMove()
{
}
