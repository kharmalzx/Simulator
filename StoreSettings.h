#pragma once

#include <QObject>
#include "MapCell.h"

class StoreSettings  : public QObject
{
	Q_OBJECT

public:
	StoreSettings(QObject *parent);
	~StoreSettings();
	
	void setTrashCount(const int& count) { m_maxCount_trash = count; }
	int getTrashCount() const { return m_maxCount_trash; }
	QVector<MapCell*>* getTrashPossiLocPtr() { return &list_trashPossiLoc; }
	void setTrashPossiLoc(const QVector<MapCell*>& list) { list_trashPossiLoc = list; }
	void setSolicitStamina(const int& stamina) { m_solicitStamina = stamina; }
	int solicitStamina() const { return m_solicitStamina; }
	int maxCustomerCount() const { return m_maxCustomerCount; }
	void setMaxCustomerCount(const int& count) { m_maxCustomerCount = count; }

private:
	int m_maxCount_trash;
	int m_solicitStamina;

	int m_maxCustomerCount;

	QVector<MapCell*> list_trashPossiLoc;
};
