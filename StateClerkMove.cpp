#include "StateClerkMove.h"

StateClerkMove::StateClerkMove(QObject *parent)
	: AbstractClerkState(parent)
{}

StateClerkMove::~StateClerkMove()
{}

void StateClerkMove::setOwner(Clerk * clerk)
{
	owner = clerk;
	storeManage = owner->getStoreManage();

}

MapCell* StateClerkMove::cellAt(const int& x, const int& y) const
{
	if (x >= 0 && x < storeManage->getMapHeight() && y >= 0 && y < storeManage->getMapWidth())
	{
		return storeManage->getMapCell(x, y);
	}
}

void StateClerkMove::getPathInFindCelllist()
{
    for (int i = 0; i < findPathCellList->size() - 1; i++) {
        QVector<MapCell*> temp = astar->getPath(findPathCellList->at(i)->x(), findPathCellList->at(i)->y(), findPathCellList->at(i + 1)->x(), findPathCellList->at(i + 1)->y());
        int size_bf = path->size();
        if (i != 0) {
            path->resize(size_bf + temp.size() - 1);
            for (int j = 1; j < temp.size(); j++)
                (*path)[size_bf + j - 1] = temp[j];
        }
        else {
            path->resize(size_bf + temp.size());
            for (int j = 0; j < temp.size(); j++)
                (*path)[size_bf + j] = temp[j];
        }

    }

    //转换为路径后清空目标list
    findPathCellList->clear();
}

void StateClerkMove::moveToTargetCell(MapCell* end)
{
    if (path->size() == 0 || end == nullptr) {
        qDebug() << "寻路的路径为空或寻路目标不存在";
        return;
    }

    owner->setLoc(path->at(0));
    MapCell* nextCell = path->at(1);
    while (owner->locAt()->x() != end->x() && owner->locAt()->y() != end->y()) {
        if (nextCell->x() == end->x() && nextCell->y() == end->y()) {
			owner->setLoc(end);
			break;
		}
        else {
			owner->setLoc(nextCell);
            path->remove(0);
			nextCell = path->at(1);

            //走路
		}
    }

    //到达目标后清空路径
    path->clear();

    switch (owner->workAction()) {
        case ClerkAction::CLEAN:
			toClean();
			break;
        case ClerkAction::LOAD:
            toLoad();
			break;
		case ClerkAction::REPLENISH:
            toReplenish();
			break;
        case ClerkAction::SOLICIT:
			toSolicit();
            break;
		default:
            break;
    }
}

void StateClerkMove::addTargetCell(MapCell* end)
{
    findPathCellList->append(end);
}

void StateClerkMove::toMove()
{
}

void StateClerkMove::toSolicit()
{
    emit moveToSolicit();
}

void StateClerkMove::toReplenish()
{
    emit moveToReplenish();
}

void StateClerkMove::toLoad()
{
    emit moveToLoad();
}

void StateClerkMove::toEnd()
{
}

void StateClerkMove::toClean()
{
    emit moveToClean();
}

void StateClerkMove::onInterruption() {

}