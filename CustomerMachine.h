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

public slots:

	void rec_moveToEnd();
	void rec_moveToCheckout();

	void rec_moveToRandomShelf();

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
