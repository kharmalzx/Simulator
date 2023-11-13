#include "ClerkMachine.h"

ClerkMachine::ClerkMachine(QObject *parent)
	: QStateMachine(parent)
{
	working = new QState(this);
	move = new StateClerkMove(this);
	load = new StateClerkLoad(working);
	slack = new StateClerkSlack(this);
	solicit = new StateClerkSolicit(working);
	replenish = new StateClerkReplenish(working);
	idle = new StateClerkIdle(this);
	rest = new StateClerkRest(this);
	stateEnd = new StateClerkEnd(this);
	stateInit = new StateClerkInit(this);
	service = new StateClerkService(working);
	history = new QHistoryState(working);

	setInitialState(stateInit);

	//初始化各状态之间的转换
	stateInit->addTransition(stateInit, &StateClerkInit::initToMove, move);
	stateInit->addTransition(stateInit, &StateClerkInit::initToEnd, stateEnd);

	move->addTransition(move, &StateClerkMove::moveToLoad, load);
	move->addTransition(move,&StateClerkMove::moveToSolicit, solicit);
	move->addTransition(move,&StateClerkMove::moveToReplenish,replenish);
	move->addTransition(move,&StateClerkMove::moveToRest,rest);
	move->addTransition(move,&StateClerkMove::moveToEnd,stateEnd);

	load->addTransition(load, &StateClerkLoad::loadToMove, move);
	load->addTransition(load, &StateClerkLoad::loadToEnd, stateEnd);

	//slack回复到历史状态
	working->addTransition(working, &QState::entered, slack);
	slack->addTransition(slack, &StateClerkSlack::slackToWork, history);

	solicit->addTransition(solicit, &StateClerkSolicit::solicitToMove, move);
	working->addTransition(solicit, &StateClerkSolicit::solicitToSlack, slack);

	replenish->addTransition(replenish, &StateClerkReplenish::replenishToMove, move);
	replenish->addTransition(replenish, &StateClerkReplenish::replenishToEnd, stateEnd);

	idle->addTransition(idle, &StateClerkIdle::idleToMove, move);
	idle->addTransition(idle, &StateClerkIdle::idleToService, service);
	idle->addTransition(idle, &StateClerkIdle::idleToSlack, slack);
	idle->addTransition(idle, &StateClerkIdle::idleToEnd, stateEnd);

	rest->addTransition(rest, &StateClerkRest::restToMove, move);
	rest->addTransition(rest, &StateClerkRest::restToEnd, stateEnd);

	service->addTransition(service, &StateClerkService::serviceToIdle, idle);
	working->addTransition(service, &StateClerkService::serviceToSlack, slack);
	service->addTransition(service, &StateClerkService::serviceToEnd, stateEnd);
	service->addTransition(service, &StateClerkService::serviceToMove, move);
	
}

ClerkMachine::~ClerkMachine()
{}

void ClerkMachine::setOwner(Clerk * clerk)
{
	owner = clerk;
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

}
