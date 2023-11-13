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

	QState* working;
	QHistoryState* history;

	Clerk* owner;
};
