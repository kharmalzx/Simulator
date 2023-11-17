#include "StateClerkReplenish.h"

StateClerkReplenish::StateClerkReplenish(QObject *parent)
	: AbstractClerkState(parent)
{
	m_replenishTimer = new QTimer(this);
	m_replenishTimer->setSingleShot(true);

	connect(m_replenishTimer, &QTimer::timeout, this, &StateClerkReplenish::toMove);
}

StateClerkReplenish::~StateClerkReplenish()
{}

void StateClerkReplenish::setOwner(Clerk * clerk)
{
	owner = clerk;
	storeManage = owner->getStoreManage();

	m_replenishTimer->setInterval(owner->getAIData()->replenishSpeed);
}

void StateClerkReplenish::onReplenishTimerTimeout()
{
	
	storeManage->replenishFacility(owner->getWorkingFacility());
	owner->setCartSize(owner->getCartSize()-1);

	

	if (owner->staminaChange(-1))
	{
		
		emit replenishToRest();
		return;
	}
	else {
		//找寻需要补货的货架
		if (owner->getCartSize() == 0) {
			owner->discardCart();
			//回默认位置去
			owner->setTargetCell();
			return;
		}

		findFaciToReplenish();
	}
}

void StateClerkReplenish::toMove()
{
	emit replenishToMove();
}

void StateClerkReplenish::findFaciToReplenish()
{
	Facility* faci = nullptr;

	if ((faci = storeManage->findFacilityToRepl()) !=nullptr) {
		owner->setWorkAction(ClerkAction::REPLENISH);
		owner->setTargetCell(faci->getWorkCell());

		toMove();
	}	
	else {
		//不需要补货，去他默认的岗位待着
		owner->discardCart();
		owner->setTargetCell();
	}
		
}
