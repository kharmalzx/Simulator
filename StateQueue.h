#pragma once

#include <qtimer.h>
#include "AbstractCustomerState.h"


class StateQueue  : public AbstractCustomerState
{
	Q_OBJECT

public:
	StateQueue(QObject* parent);
	~StateQueue();

	void onEntry(QEvent* event) override;
	void ToMove() override;
	void setOwner(Customer* owner) override;

	int getFacilityPopulation();

public slots:
	void OnInterruption() override;
	void onQueue2Timeout();
	void checkQueueStateChange();


signals:
    void QueueToMove();
	void QueueToFetch();
	

private:
	Customer* owner;
	QTimer* timer_queue2;
	StoreManage* storeManage;

	void ToFetch();
};
