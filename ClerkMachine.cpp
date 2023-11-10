#include "ClerkMachine.h"

ClerkMachine::ClerkMachine(QObject *parent)
	: QStateMachine(parent)
{
	move = new StateClerkMove(this);
	load = new StateClerkLoad(this);
	slack = new StateClerkSlack(this);
	solicit = new StateClerkSolicit(this);
	replenish = new StateClerkReplenish(this);
	idle = new StateClerkIdle(this);
	rest = new StateClerkRest(this);
	stateEnd = new StateClerkEnd(this);
	stateInit = new StateClerkInit(this);
	service = new StateClerkService(this);

	addState(move);
	addState(load);
	addState(slack);
	addState(solicit);
	addState(replenish);
	addState(idle);
	addState(rest);
	addState(stateEnd);
	addState(stateInit);
	addState(service);

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

	//slack回复到历史状态，根据信号的不同，转换到不同的状态
	slack->addTransition(slack, &StateClerkSlack::slackToMove, move);
	slack->addTransition(service);
	slack->addTransition(solicit);
	slack->addTransition(replenish);
	connect(slack,&StateClerkSlack::slackToWork,this,&ClerkMachine::slackBackToWork);

	solicit->addTransition(solicit, &StateClerkSolicit::solicitToMove, move);
	solicit->addTransition(solicit, &StateClerkSolicit::solicitToSlack, slack);

	replenish->addTransition(replenish, &StateClerkReplenish::replenishToMove, move);
	replenish->addTransition(replenish, &StateClerkReplenish::replenishToEnd, stateEnd);

	idle->addTransition(idle, &StateClerkIdle::idleToMove, move);
	idle->addTransition(idle, &StateClerkIdle::idleToService, service);
	idle->addTransition(idle, &StateClerkIdle::idleToSlack, slack);
	idle->addTransition(idle, &StateClerkIdle::idleToEnd, stateEnd);

	rest->addTransition(rest, &StateClerkRest::restToMove, move);
	rest->addTransition(rest, &StateClerkRest::restToEnd, stateEnd);

	service->addTransition(service, &StateClerkService::serviceToIdle, idle);
	service->addTransition(service, &StateClerkService::serviceToSlack, slack);
	service->addTransition(service, &StateClerkService::serviceToEnd, stateEnd);
	service->addTransition(service, &StateClerkService::serviceToMove, move);
}

ClerkMachine::~ClerkMachine()
{}

void ClerkMachine::setOwner(Clerk * clerk)
{
	owner = clerk;
}

void ClerkMachine::slackBackToWork(int hs)
{
	QHistoryState* historyState = static_cast<QHistoryState*>(sender());
}
