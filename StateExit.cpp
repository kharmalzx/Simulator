#include "StateExit.h"

StateExit::StateExit(QObject *parent) : AbstractCustomerState(parent)
{

}

StateExit::~StateExit()
{}

void StateExit::onEntry(QEvent* e)
{
	owner->deleteLater();
}

void StateExit::setOwner(Customer * owner)
{
	this->owner = owner;	
}

void StateExit::toMove()
{
}
