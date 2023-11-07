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

public slots:
	void onInterruption() override;

private:
	void toMove() override;
};
