#pragma once

#include <QState>
#include "AbstractClerkState.h"

class StateClerkSolicit  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkSolicit(QObject *parent);
	~StateClerkSolicit();

	void setOwner(Clerk* clerk) override;
	void onEntry(QEvent* event) override;
	void onExit(QEvent* event) override;

public slots :
	void onInterruption() override;
	void onSolicitTimerTimeout();

signals:
	void solicitToMove();
	void solicitToIdle();
	void solicitToSlack();
	void solicitToRest();

private:
	Clerk* owner;
	QTimer* m_solicitTimer;
	StoreManage* storeManage;
	StoreSettings* storeSettings;
	
	void toMove() override;
	void toIdle();
	void toRest();
};
