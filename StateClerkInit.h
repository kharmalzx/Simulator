#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkInit  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkInit(QObject *parent);
	~StateClerkInit();

	void setOwner(Clerk* clerk) override;

public slots:
	void onInterruption() override;

signals:
	void initToMove();
	void initToEnd();

private:
	Clerk* owner;
	void toMove() override;
};
