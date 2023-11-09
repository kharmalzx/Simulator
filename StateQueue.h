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
	
	void setOwner(Customer* owner) override;

	int getFacilityPopulation();

public slots:
	void onInterruption() override;
	void onQueue2Timeout();
	void checkQueueStateChange();


signals:
    void queueToMove();
	void queueToFetch();
	void queueToCheckout();

private:
	Customer* owner;
	QTimer* timer_queue2;
	StoreManage* storeManage;

	void toFetch();
	void toMove() override;
	void toCheckout();

	void clearQueueInfoWhenLeave();
	void clearQueueInfoWhenFaci();
};
