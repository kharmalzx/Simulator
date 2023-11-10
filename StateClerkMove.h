#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkMove  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkMove(QObject *parent);
	~StateClerkMove();

	void setOwner(Clerk* clerk) override;

public slots:
	void onInterruption() override;

signals:
	void moveToLoad();
	void moveToSolicit();
	void moveToReplenish();
	void moveToRest();
	void moveToEnd();

private:
	Clerk* m_owner;
	void toMove() override;
};
