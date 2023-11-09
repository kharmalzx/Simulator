#include "StateCheckout.h"

StateCheckout::StateCheckout(QObject *parent) :AbstractCustomerState(parent)
{
	checkoutTimer = new QTimer(this);
	checkoutTimer->setSingleShot(true);

	connect(checkoutTimer, &QTimer::timeout, this, &StateCheckout::onCheckoutTimerOut);
}

StateCheckout::~StateCheckout()
{}

void StateCheckout::onEntry(QEvent * e)
{

}

void StateCheckout::setOwner(Customer* owner)
{
	this->owner = owner;
	this->storeManage = owner->storeManage;

	Facility* faci = storeManage->getFaciPtr(owner->queueInfo.facilitySn);

	checkoutTime = owner->AIData.coefficient_service * faci->service_tick;
	checkoutTimer->setInterval(checkoutTime);

	connect(checkoutTimer, &QTimer::timeout, this, &StateCheckout::toMove);
	checkoutTimer->start();
}


void StateCheckout::onInterruption() {

	checkoutTimer->stop();
}

void StateCheckout::toMove()
{
	owner->findCommoditySn = 0;
	owner->queueInfo.facilitySn = 0;
	owner->queueInfo.isInQueue1 = false;

	emit checkoutToMove();
}

void StateCheckout::onCheckoutTimerOut()
{
	storeManage->customerPay(owner);

	toMove();
}
