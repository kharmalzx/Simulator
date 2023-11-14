#pragma once

#include <QState>
#include "AbstractClerkState.h"

class StateClerkSolicit  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkSolicit(QObject *parent);
	~StateClerkSolicit();

	void setOwner(Clerk* clerk) override;

public slots :
	void onInterruption() override;

signals:
	void solicitToMove();

private:
	Clerk* owner;
	void toMove() override;
};
