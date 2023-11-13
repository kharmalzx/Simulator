#pragma once

#include <QObject>
#include "ClerkInfo.h"
#include "ClerkMachine.h"
#include "StoreManage.h"

class Clerk  : public QObject
{
	Q_OBJECT

public:
	Clerk(QObject *parent);
	~Clerk();

	void setPreviousState(AbstractClerkState* state) { m_previousState = state; };
	AbstractClerkState* getPreviousState() { return m_previousState; }
	void setAIData(ClerkAIData data) { m_AIData = data; }
	ClerkAIData* getAIData() { return &m_AIData; }
	void setStoreManage(StoreManage* storeManage) { m_storeManage = storeManage; }
	StoreManage* getStoreManage() { return m_storeManage; }
	MapCell* locAt() const { return currentCell; }
	void setLoc(MapCell* cell) { *currentCell = *cell; }

private:
	ClerkMachine* m_machine;
	AbstractClerkState* m_previousState;

	ClerkAIData m_AIData;
	StoreManage* m_storeManage;

	MapCell* currentCell;
};
