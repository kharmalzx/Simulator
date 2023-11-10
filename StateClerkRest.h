#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkRest  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkRest(QObject *parent);
	~StateClerkRest();

	void setOwner(Clerk* clerk) override;

public slots:
	void onInterruption() override;

signals:
	void restToMove();
	void restToEnd();

private:
	Clerk* owner;
	void toMove() override;
};
