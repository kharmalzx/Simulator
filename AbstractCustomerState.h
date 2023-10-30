#pragma once

#include <QState>
#include <QEvent>


class AbstractCustomerState  : public QState
{
	Q_OBJECT

public:
	AbstractCustomerState(QObject *parent);
	~AbstractCustomerState();

public slots:
	virtual void OnInterruption();
	virtual void ToMove();
};
