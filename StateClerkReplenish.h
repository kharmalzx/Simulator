#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkReplenish  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkReplenish(QObject *parent);
	~StateClerkReplenish();

	void setOwner(Clerk* clerk) override;

public slots:
	void onInterruption() override;

signals:
	void replenishToMove();
	void replenishToEnd();

private:
	Clerk* owner;
	void toMove() override;
};
