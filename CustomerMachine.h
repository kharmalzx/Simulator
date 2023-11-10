#pragma once

#include <QStateMachine>
#include "CustomerStates.h"

class CustomerMachine  : public QStateMachine
{
	Q_OBJECT

public:
	CustomerMachine(QObject *parent,Customer* owner);
	~CustomerMachine();

	void setOwner(Customer* owner);
public slots:


private:
    StateEnter* enter;
    StateMove* move;
    StateQueue* queue;
	StateFetch* fetch;
	StateCheckout* checkout;
	StateExit* exit;
	

	Customer* owner;

};
