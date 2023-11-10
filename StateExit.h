#pragma once

#include <QState>
#include "AbstractCustomerState.h"

class StateExit  : public AbstractCustomerState
{
	Q_OBJECT

public:
	StateExit(QObject *parent);
	~StateExit();

	void onEntry(QEvent * e) override;
	void setOwner(Customer* owner) override;

public slots:
	void onInterruption() override;

private:
	Customer* owner;
	StoreManage* storeManage;

	void toMove() override;
};
