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
	void moveToPurchase();
	void purchaseToMove();
	void moveToCheckout();
	void checkoutToMove();
	void queueStarted();
	void queueFinished();
	void enterToMove();
	void moveToExit();
	void moveToCheckout();
	void moveToMove();

	void sig_toOwner_moveToRandomShelf();
	void sig_toOwner_moveToPurchase();

public slots:

	void rec_moveToEnd();
	void rec_moveToCheckout();

	void rec_moveToRandomShelf();
	void rec_moveToPurchase();

private:
    StateEnter* enter;
    StateMove* move;
    StatePurchase* purchase;
    StateCheckout* checkout;
    StateExit* exit;
    StateSlack* slack;

	Customer* owner;

	void initConnectToOwner();

};
