#pragma once

#include <QState>
#include "AbstractClerkState.h"

class StateClerkWorking  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkWorking(QObject *parent);
	~StateClerkWorking();

	void setOwner(Clerk *owner);
	void onEntry(QEvent *) override;
	void onExit(QEvent *) override;

	void toSlack();
	void toRest();

public slots:
	void onInterruption() override;

signals:
	void workingToEnd();
	void workingToSlack();
	void workingToRest();

private:
	Clerk *owner;
	StoreManage* storeManage;
	QTimer* m_slackTimer;


	bool checkIfStraightToRest();
	bool checkIfStraightToSlack();
	void toMove() override;
	
};
