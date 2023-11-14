#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkSlack  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkSlack(QObject *parent);
	~StateClerkSlack();

	void setOwner(Clerk* clerk) override;
	void onEntry(QEvent* event) override;

public slots:
	void onInterruption() override;
	

signals:
	void slackToWork();

private:
	Clerk* owner;
	StoreManage* storeManage;

	QTimer* m_slackTimer;

	void toMove() override;
	void toWork();
};
