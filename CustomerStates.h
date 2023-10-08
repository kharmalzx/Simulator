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
	STATE_SLACK,
	STATE_CHECKOUT
};

class StatePurchase : public QState
{
	Q_OBJECT
public:
	explicit StatePurchase(QState* parent = nullptr) { state = CustomerState::STATE_PURCHASE; };
	void onEntry(QEvent* e) override;
	void onExit(QEvent* e) override;
	int getState() const { return state; };

private:
	int state;
};

class StateMove: public QState
{
	Q_OBJECT
public:
	explicit StateMove(QState* parent = nullptr) { state = CustomerState::STATE_MOVE; };
	void onEntry (QEvent* e) override;
	void onExit(QEvent* e) override;
	int getState() const { return state; };

private:
	int state;

};

class StateQueue: public QState
{
	Q_OBJECT
public:
	explicit StateQueue(QState* parent = nullptr) { state = CustomerState::STATE_QUEUE; };
	void onEntry(QEvent* e) override;
	void onExit(QEvent* e) override;
	int getState() const { return state; };

private:
	int state;

};

class StateEnter: public QState
{
	Q_OBJECT
public:
	explicit StateEnter(QState* parent = nullptr) { state = CustomerState::STATE_ENTER; };
	void onEntry(QEvent* e) override;
	void onExit(QEvent* e) override;
	int getState() const { return state; };

private:
	int state;

};

class StateExit : public QState
{
	Q_OBJECT
public:
	explicit StateExit(QState* parent = nullptr) { state = CustomerState::STATE_EXIT; };
	void onEntry(QEvent* e) override;
	void onExit(QEvent* e) override;
	int getState() const { return state; };

private:
	int state;
};

class StateSlack: public QState
{
	Q_OBJECT
public:
	explicit StateSlack(QState* parent = nullptr) { state = CustomerState::STATE_SLACK; };
	void onEntry(QEvent* e) override;
	void onExit(QEvent* e) override;
	int getState() const { return state; };

private:
	int state;
};

class StateCheckout: public QState
{
	Q_OBJECT
public:
	explicit StateCheckout(QState* parent = nullptr) { state = CustomerState::STATE_CHECKOUT; };
	void onEntry(QEvent* e) override;
	void onExit(QEvent* e) override;
	int getState() const { return state; };

private:
	int state;
};

#endif // CUSTOMERSTATES_H