#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkService  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkService(QObject *parent);
	~StateClerkService();

	void setOwner(Clerk* clerk);

public slots:
	void onInterruption() override;

signals:
	void serviceToMove();
	void serviceToIdle();
	void serviceToSlack();
	void serviceToEnd();

private:
	Clerk* owner;
	void toMove() override;
};
