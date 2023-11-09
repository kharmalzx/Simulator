#pragma once

#include <QState>
#include "AbstractCustomerState.h"

class StateCheckout  : public AbstractCustomerState
{
	Q_OBJECT

public:
	StateCheckout(QObject *parent);
	~StateCheckout();

	void onEntry(QEvent* e) override;
	void setOwner(Customer* owner) override;

public slots:
	void onInterruption() override;

signals:
	void checkoutToMove();

private:
	Customer* owner;
	StoreManage* storeManage;
	int checkoutTime;
	QTimer* checkoutTimer;

	void toMove() override;
	void onCheckoutTimerOut();
};
