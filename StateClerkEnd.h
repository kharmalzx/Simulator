#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkEnd  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkEnd(QObject *parent);
	~StateClerkEnd();

	void setOwner(Clerk* clerk) override;

public slots:
	void onInterruption() override;

private:
	void toMove() override;
};
