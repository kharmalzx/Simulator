#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkLoad  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkLoad(QObject *parent);
	~StateClerkLoad();

	void setOwner(Clerk* clerk) override;

public slots:
	void onInterruption() override;

signals:
	void loadToMove();
	void loadToEnd();

private:
	Clerk* owner;
	void toMove() override;
};
