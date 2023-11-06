#pragma once

#include "AbstractCustomerState.h"

class StateFetch  : public AbstractCustomerState
{
	Q_OBJECT

public:
	StateFetch(QObject *parent);
	~StateFetch();

	void setOwner(Customer* owner) override;
	void onEntry(QEvent* event) override;
	void ToMove() override;

public slots:
	void onFetchTimerOut();
	void OnInterruption() override;


signals:
	void fetchToMove();
	

private:
	QTimer* fetchTickTimer;
	Customer* owner;
	StoreManage* storeManage;

	Facility* targetFacility;

	int tick;
	int count_remain;
};
