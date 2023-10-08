#pragma once

#ifndef CUSTOMERSTATES_H
#define CUSTOMERSTATES_H

#include <qstate.h>
#include <qsignaltransition.h>

enum CustomerState
{
	STATE_PURCHASE,
	STATE_MOVE,
	STATE_QUEUE,
	STATE_ENTER,
	STATE_EXIT,
	STATE_SLACK
};

class StatePurchase : public QState
{
	Q_OBJECT
public:
	explicit StatePurchase(QState* parent = nullptr) { state = CustomerState::STATE_PURCHASE; };
	void onEntry(QEvent* e) override;
	void onExit(QEvent* e) override;
	void addState(QState* targetState);
	int getState() const { return state; };

private:
	int state;
};

class StateMove: public QState
{
	Q_OBJECT
public:
	explicit StateMove(QState* parent = nullptr);
};

class StateQueue: public QState
{
	Q_OBJECT
public:
	explicit StateQueue(QState* parent = nullptr);

};

class StateEnter: public QState
{
	Q_OBJECT
public:
	explicit StateEnter(QState* parent = nullptr);


};

class StateExit: public QState
{
	Q_OBJECT
public:
	explicit StateExit(QState* parent = nullptr);

};

class StateSlack: public QState
{
	Q_OBJECT
public:
	explicit StateSlack(QState* parent = nullptr);

};

class StateCheckout: public QState
{
	Q_OBJECT
public:
	explicit StateCheckout(QState* parent = nullptr);

};

#endif // CUSTOMERSTATES_H