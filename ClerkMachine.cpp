#include "ClerkMachine.h"

ClerkMachine::ClerkMachine(QObject *parent)
	: QStateMachine(parent)
{
	working = new StateClerkWorking(this);
	load = new StateClerkLoad(working);
	solicit = new StateClerkSolicit(working);
	replenish = new StateClerkReplenish(working);
	service = new StateClerkService(working);
	idle = new StateClerkIdle(working);
	clean = new StateClerkClean(working);
	history = new QHistoryState(working);
	move = new StateClerkMove(working);

	rest = new StateClerkRest(this);
	stateEnd = new StateClerkEnd(this);
	stateInit = new StateClerkInit(this);
	slack = new StateClerkSlack(this);
	

	setInitialState(stateInit);
	initIdleTransitions();
	initLoadTransitions();
	initMoveTransitions();
	initReplenishTransitions();
	initRestTransitions();
	initServiceTransitions();
	initSlackTransitions();
	initSolicitTransitions();
	initStateEndTransitions();
	initStateInitTransitions();
	initWorkingTransitions();
	


}

ClerkMachine::~ClerkMachine()
{}

void ClerkMachine::setOwner(Clerk * clerk)
{
	owner = clerk;
	working->setOwner(clerk);
	move->setOwner(clerk);
	load->setOwner(clerk);
	slack->setOwner(clerk);
	solicit->setOwner(clerk);
	replenish->setOwner(clerk);
	idle->setOwner(clerk);
	rest->setOwner(clerk);
	stateEnd->setOwner(clerk);
	stateInit->setOwner(clerk);
	service->setOwner(clerk);
	clean->setOwner(clerk);

}

void ClerkMachine::initWorkingTransitions()
{
	working->addTransition(working, &StateClerkWorking::workingToSlack, slack);
	working->addTransition(working, &StateClerkWorking::workingToRest, rest);
	//这里还没实装
	working->addTransition(working,&StateClerkWorking::workingToEnd, stateEnd);
}

void ClerkMachine::initMoveTransitions()
{
	move->addTransition(move, &StateClerkMove::moveToLoad, load);
	move->addTransition(move, &StateClerkMove::moveToSolicit, solicit);
	move->addTransition(move, &StateClerkMove::moveToReplenish, replenish);
}

void ClerkMachine::initLoadTransitions()
{
	load->addTransition(load, &StateClerkLoad::loadToMove, move);
}

void ClerkMachine::initSlackTransitions()
{
	slack->addTransition(slack, &StateClerkSlack::slackToWork, history);
}

void ClerkMachine::initSolicitTransitions()
{
	solicit->addTransition(solicit, &StateClerkSolicit::solicitToMove, move);
}

void ClerkMachine::initReplenishTransitions()
{
	replenish->addTransition(replenish, &StateClerkReplenish::replenishToMove, move);
}

void ClerkMachine::initIdleTransitions()
{
	idle->addTransition(idle, &StateClerkIdle::idleToService, service);
	idle->addTransition(idle,&StateClerkIdle::idleToMove,move);
}

void ClerkMachine::initRestTransitions()
{
	rest->addTransition(rest, &StateClerkRest::restToEnd, stateEnd);
	rest->addTransition(rest, &StateClerkRest::restToWork, history);
}

void ClerkMachine::initStateEndTransitions()
{
}

void ClerkMachine::initStateInitTransitions()
{
	stateInit->addTransition(stateInit, &StateClerkInit::initToMove, move);
	stateInit->addTransition(stateInit, &StateClerkInit::initToEnd, stateEnd);
}

void ClerkMachine::initServiceTransitions()
{
	service->addTransition(service, &StateClerkService::serviceToIdle, idle);
	service->addTransition(service, &StateClerkService::serviceToMove, move);
}

void ClerkMachine::initCleanTransitions()
{
	clean->addTransition(clean, &StateClerkClean::cleanToMove, move);
}
