#pragma once

#include <QStateMachine>
#include <qhistorystate.h>
#include "ClerkStates.h"

class ClerkMachine  : public QStateMachine
{
	Q_OBJECT

public:
	ClerkMachine(QObject *parent);
	~ClerkMachine();

	void setOwner(Clerk* clerk);

private:
	StateClerkMove* move;
	StateClerkLoad* load;
	StateClerkSlack* slack;
	StateClerkSolicit* solicit;
	StateClerkReplenish* replenish;
	StateClerkIdle* idle;
	StateClerkRest* rest;
	StateClerkEnd* stateEnd;
	StateClerkInit* stateInit;
	StateClerkService* service;
	StateClerkWorking* working;
	StateClerkClean* clean;
	QHistoryState* history;

	Clerk* owner;

	void initWorkingTransitions();
	void initMoveTransitions();
	void initLoadTransitions();
	void initSlackTransitions();
	void initSolicitTransitions();
	void initReplenishTransitions();
	void initIdleTransitions();
	void initRestTransitions();
	void initStateEndTransitions();
	void initStateInitTransitions();
	void initServiceTransitions();
	void initCleanTransitions();

};
