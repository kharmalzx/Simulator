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

public slots:
	void onInterruption() override;

signals:
	void moveToLoad();
	void moveToSolicit();
	void moveToReplenish();
	void moveToRest();
	void moveToEnd();

private:
	Clerk* owner;
	StoreManage* storeManage;
	QVector<MapCell*>* path;
	QVector<MapCell*>* findPathCellList;
	AStarPathfinding* astar;

	MapCell* cellAt(const int& x, const int& y) const;
	void getPathInFindCelllist();
	void moveToTargetCell(MapCell* end);

	void toMove() override;
	void toSolicit();
	void toReplenish();
	void toRest();
	void toLoad();
	void toEnd();
};
