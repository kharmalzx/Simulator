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
	void onEntry(QEvent* event) override;
	void onExit(QEvent* event) override;

public slots:
	void onInterruption() override;
	void onServiceFinished();

signals:
	void serviceToMove();
	void serviceToIdle();

private:
	Clerk* owner;
	StoreManage* storeManage;
	QTimer* m_serviceTimer;
	
	void service();
	void toMove() override;
	void toIdle();
};
