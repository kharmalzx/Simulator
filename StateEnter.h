#pragma once

#include <QState>
#include "AbstractCustomerState.h"

class StateEnter  : public AbstractCustomerState
{
	Q_OBJECT

public:
	StateEnter(QObject *parent);
	~StateEnter();

	void ToMove() override;
	void setOwner(Customer* owner) override;

public slots:
	void OnInterruption() override;

signals:
	void enterTomove();

private:
	Customer* owner;
};
