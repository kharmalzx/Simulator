#include "StateClerkRest.h"

StateClerkRest::StateClerkRest(QObject *parent)
	: AbstractClerkState(parent)
{
	m_stateMoveToRest = new StateClerkMove(this);
	m_restTimer = new QTimer(this);

	connect(m_restTimer, &QTimer::timeout, this, &StateClerkRest::toMove);
}

StateClerkRest::~StateClerkRest()
{}

void StateClerkRest::setOwner(Clerk * clerk)
{
	owner = clerk;
	storeManage = owner->getStoreManage();
}

void StateClerkRest::onEntry(QEvent* event)
{
	//进来之后直接走去房间休息
	MapCell* c = storeManage->findRestChair();

	if (c != nullptr) {
		m_stateMoveToRest->addTargetCell(c);
		m_stateMoveToRest->getPathInFindCelllist();
		m_stateMoveToRest->moveToTargetCell(c);

		m_restTimer->start(Clerk::restTime);
		
	}
	else {
		//这里还要处理休息室人太多的问题，不过暂时假定位置充足

	}
}

void StateClerkRest::onInterruption()
{
	toMove();
}

void StateClerkRest::toMove()
{
	m_restTimer->stop();

	//去往自己刚才工作的位置，需要判断岗位是否被人代理
	if (owner->getWorkCell()) {
		m_stateMoveToRest->addTargetCell(owner->getWorkCell());
		m_stateMoveToRest->getPathInFindCelllist();
		m_stateMoveToRest->moveToTargetCell(owner->getWorkCell());
	}
	

	emit restToWork();
}
