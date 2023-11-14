#pragma once

#include <QObject>
#include "MapCell.h"

class StoreSettings  : public QObject
{
	Q_OBJECT

public:
	StoreSettings(QObject *parent);
	~StoreSettings();
	
	void setTrashCount(const int& count) { maxCount_trash = count; }
	int getTrashCount() const { return maxCount_trash; }
	QVector<MapCell*>* getTrashPossiLocPtr() { return &list_trashPossiLoc; }
	void setTrashPossiLoc(const QVector<MapCell*>& list) { list_trashPossiLoc = list; }

private:
	int maxCount_trash;
	QVector<MapCell*> list_trashPossiLoc;
};
