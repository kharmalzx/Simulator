#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkIdle  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkIdle(QObject *parent);
	~StateClerkIdle();

	void setOwner(Clerk* clerk) override;
	void onEntry(QEvent* e) override;

public slots:
	void onInterruption() override;

signals:
	void idleToMove();
	void idleToService();
	//不清楚揽客的时候是否idle，先写着
	void idleToSolicit();

private:
	Clerk* owner;

	//可能会去打扫
	void toMove() override;
	void toService();
};
