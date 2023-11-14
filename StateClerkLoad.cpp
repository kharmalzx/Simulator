#include "StateClerkLoad.h"

StateClerkLoad::StateClerkLoad(QObject *parent)
	: AbstractClerkState(parent)
{
	m_loadTimer = new QTimer(this);
	m_loadTimer->setSingleShot(true);

	connect(m_loadTimer, &QTimer::timeout, this, &StateClerkLoad::onLoadTimeOut);
}

StateClerkLoad::~StateClerkLoad()
{}

void StateClerkLoad::setOwner(Clerk * clerk)
{
	owner = clerk;
	storeManage = owner->getStoreManage();
	m_loadTimer->setInterval(owner->getAIData()->loadSpeed);
}

void StateClerkLoad::onEntry(QEvent* event)
{
	Q_UNUSED(event);
	owner->createCart();

	m_loadTimer->start();
}

void StateClerkLoad::onLoadTimeOut()
{
	owner->setCartSize(storeManage->getCharacterSettingsPtr()->cartSize());
	toMove();
}

void StateClerkLoad::toMove()
{
	owner->setWorkAction(ClerkAction::MOVE);
	emit loadToMove();
}
