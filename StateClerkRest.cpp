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
	//����֮��ֱ����ȥ������Ϣ
	MapCell* c = storeManage->findRestChair();

	if (c != nullptr) {
		m_stateMoveToRest->addTargetCell(c);
		m_stateMoveToRest->getPathInFindCelllist();
		m_stateMoveToRest->moveToTargetCell(c);

		m_restTimer->start(Clerk::restTime);
		
	}
	else {
		//���ﻹҪ������Ϣ����̫������⣬������ʱ�ٶ�λ�ó���

	}
}

void StateClerkRest::onInterruption()
{
	toMove();
}

void StateClerkRest::toMove()
{
	m_restTimer->stop();

	//ȥ���Լ��ղŹ�����λ�ã���Ҫ�жϸ�λ�Ƿ��˴���
	if (owner->getWorkCell()) {
		m_stateMoveToRest->addTargetCell(owner->getWorkCell());
		m_stateMoveToRest->getPathInFindCelllist();
		m_stateMoveToRest->moveToTargetCell(owner->getWorkCell());
	}
	

	emit restToWork();
}
