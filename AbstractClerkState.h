#pragma once

#include <QState>
#include "Clerk.h"

class AbstractClerkState  : public QState
{
	Q_OBJECT

public:
	AbstractClerkState(QObject *parent);
	~AbstractClerkState();

	virtual void setOwner(Clerk* clerk) = 0;

public slots:
	virtual void onInterruption() = 0;

private:
	virtual void toMove() = 0;
};
