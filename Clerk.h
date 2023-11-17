#pragma once

#include <QObject>
#include "ClerkInfo.h"
#include "ClerkMachine.h"
#include "StoreManage.h"
#include "Cart.h"

class Clerk  : public QObject
{
	Q_OBJECT

public:

	static int slackTime;
	static int restTime;

	Clerk(QObject *parent);
	~Clerk();

	void setAIData(ClerkAIData data) { m_AIData = data; }
	ClerkAIData* getAIData() { return &m_AIData; }
	void setStoreManage(StoreManage* storeManage) { m_storeManage = storeManage; }
	StoreManage* getStoreManage() { return m_storeManage; }
	MapCell* locAt() const { return currentCell; }
	void setLoc(MapCell* cell) { *currentCell = *cell; }
	void setWillSlack(bool willSlack) { this->willSlack = willSlack; }
	bool getWillSlack() { return willSlack; }
	void setWillRest(bool willRest) { this->willRest = willRest; }
	bool getWillRest() { return willRest; }
	MapCell* getWorkCell() { return workCell; }
	void setWorkCell(MapCell* workCell) { this->workCell = workCell; }
	int workAction() const { return m_workAction; }
	void setWorkAction(const int& workAction) { m_workAction = workAction; }
	void setWorkingFacility(Facility* facility) { m_workingFacility = facility; }
	Facility* getWorkingFacility() { return m_workingFacility; }
	void createCart();
	void setCartSize(int size) { cart->setSize(size); }
	int getCartSize() { return cart->getSize(); }
	void discardCart() { delete cart; }
	//改变体力值，返回值表示是否体力不足
	bool staminaChange(const int& change);
	void setTargetCell(MapCell* cell) { targetCell = cell; }

private:

	QMutex staminaMutex;

	bool willSlack;
	bool willRest;
	//将要执行的动作
	int m_workAction;
	Cart* cart;
	Facility* m_workingFacility;

	ClerkMachine* m_machine;

	ClerkAIData m_AIData;
	StoreManage* m_storeManage;

	MapCell* currentCell;
	//包括站着不动的地点，以及补货的地点
	MapCell* workCell;
	MapCell* targetCell;

};
