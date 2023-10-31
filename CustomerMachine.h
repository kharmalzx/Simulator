#pragma once

#include <QStateMachine>
#include "CustomerStates.h"

class CustomerMachine  : public QStateMachine
{
	Q_OBJECT

public:
	CustomerMachine(QObject *parent,Customer* owner);
	~CustomerMachine();

signals:
    void enterToMove();

public slots:


private:
    StateEnter* enter;
    StateMove* move;
    StateQueue* queue;
	StateFetch* fetch;

	Customer* owner;

};
