#pragma once

#include <QState>
#include <QEvent>

#include "Customer.h"
#include "CustomerMachine.h"


class AbstractCustomerState  : public QState
{
	Q_OBJECT

public:

	AbstractCustomerState(QObject* parent) {};

	virtual void setOwner(Customer* owner) = 0;

public slots:
	virtual void OnInterruption() = 0;
	

private:

	virtual void ToMove() = 0;
};
