#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkSlack  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkSlack(QObject *parent);
	~StateClerkSlack();

	void setOwner(Clerk* clerk) override;

public slots:
	void onInterruption() override;

signals:
	void slackToMove();
	void slackToWork(int targetState);

private:
	Clerk* owner;
	void toMove() override;
};
