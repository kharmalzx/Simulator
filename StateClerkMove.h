#pragma once

#include <QObject>
#include "AbstractClerkState.h"

class StateClerkMove  : public AbstractClerkState
{
	Q_OBJECT

public:
	StateClerkMove(QObject *parent);
	~StateClerkMove();

	void setOwner(Clerk* clerk) override;
	void getPathInFindCelllist();
	void moveToTargetCell(MapCell* end);
	void addTargetCell(MapCell* end);

public slots:
	void onInterruption() override;

signals:
	void moveToLoad();
	void moveToSolicit();
	void moveToReplenish();
	void moveToClean();

private:
	Clerk* owner;
	StoreManage* storeManage;
	QVector<MapCell*>* path;
	QVector<MapCell*>* findPathCellList;
	AStarPathfinding* astar;

	MapCell* cellAt(const int& x, const int& y) const;
	
	void toMove() override;
	void toSolicit();
	void toReplenish();
	void toLoad();
	void toEnd();
	void toClean();
};
