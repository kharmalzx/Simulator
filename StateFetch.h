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
	//���ڶ�������ʱ������ʱ����ȡ
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
