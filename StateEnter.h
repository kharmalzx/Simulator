#pragma once

#include <QState>
#include "AbstractCustomerState.h"

class StateEnter  : public AbstractCustomerState
{
	Q_OBJECT

public:
	StateEnter(QObject *parent);
	~StateEnter();

	void toMove() override;
	void setOwner(Customer* owner) override;

public slots:
	void onInterruption() override;

signals:
	void enterTomove();

private:
	Customer* owner;
};
