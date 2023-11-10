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

public slots:
	void onInterruption() override;

signals:
	void idleToMove();
	void idleToService();
	void idleToEnd();
	void idleToSlack();

private:
	void toMove() override;
};
