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
	void onEntry(QEvent* event) override;

public slots:
	void onInterruption() override;

signals:
	void restToMove();
	void restToEnd();
	void restToWork();

private:
	Clerk* owner;
	StoreManage* storeManage;
	StateClerkMove* m_stateMoveToRest;

	QTimer* m_restTimer;

	void toMove() override;
};
