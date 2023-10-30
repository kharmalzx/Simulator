#pragma once

#include <QStateMachine>
#include "CustomerStates.h"

class CustomerMachine  : public QStateMachine
{
	Q_OBJECT

public:
	CustomerMachine(QObject *parent,Customer* owner);
	~CustomerMachine();

signals:
	//按照名字区别发给子状态还是owner，状态机自身不初始化和owner的连接
	void sig_toStates_moveToPurchase();
	void sig_toStates_purchaseToMove();
	void sig_toStates_moveToCheckout();
	void sig_toStates_checkoutToMove();
	void sig_toStates_queueStarted();
	void queueFinished();
	void sig_toStates_enterToMove();
	void sig_toStates_moveToExit();
	void sig_toStates_moveToMove();


	void sig_toOwner_moveToRandomShelf();
	void sig_toOwner_moveToPurchase();

public slots:

	void rec_fromOwner_moveToEnd();
	void rec_fromOwner_moveToCheckout();
	void rec_fromOwner_moveToPurchase();

	void rec_fromStates_moveToRandomShelf();
	void rec_fromStates_moveToPurchase();

private:
    StateEnter* enter;
    StateMove* move;
    StatePurchase* purchase;
    StateCheckout* checkout;
    StateExit* exit;

	Customer* owner;

};
