#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkClean  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkClean(QObject *parent);
	~StateClerkClean();

	void setOwner(Clerk *owner);

public slots:
	void onInterruption() override;

signals:
	void cleanToMove();

private:
	Clerk *owner;
	void toMove() override;
};
