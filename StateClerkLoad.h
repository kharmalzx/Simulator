#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkLoad  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkLoad(QObject *parent);
	~StateClerkLoad();

	void setOwner(Clerk* clerk) override;
	void onEntry(QEvent* event) override;

public slots:
	void onInterruption() override;
	void onLoadTimeOut();

signals:
	void loadToMove();

private:
	Clerk* owner;
	StoreManage* storeManage;
	QTimer* m_loadTimer;

	void toMove() override;
};
