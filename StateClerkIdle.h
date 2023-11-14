#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkIdle  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkIdle(QObject *parent);
	~StateClerkIdle();

	void setOwner(Clerk* clerk) override;
	void onEntry(QEvent* e) override;

public slots:
	void onInterruption() override;

signals:
	void idleToMove();
	void idleToService();
	//��������͵�ʱ���Ƿ�idle����д��
	void idleToSolicit();

private:
	Clerk* owner;

	//���ܻ�ȥ��ɨ
	void toMove() override;
	void toService();
};
