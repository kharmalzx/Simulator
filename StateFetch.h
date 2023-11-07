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
	

public slots:
	void onFetchTimerOut();
	void onInterruption() override;
	void onCheckReplenishment();

signals:
	void fetchToMove();
	

private:
	//用于读条，计时器结束时才拿取
	QTimer* fetchTickTimer;
	Customer* owner;
	StoreManage* storeManage;

	Facility* targetFacility;

	int tick;
	int count_remain;

	void fetchCommodity();
	bool canFetchCommodity();

	void toMove() override;

};
