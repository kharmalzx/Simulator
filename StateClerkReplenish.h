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
	void onReplenishTimerTimeout();

signals:
	void replenishToMove();
	void replenishToRest();

private:
	Clerk* owner;
	StoreManage* storeManage;

	QTimer* m_replenishTimer;

	void toMove() override;
	void findFaciToReplenish();
};
