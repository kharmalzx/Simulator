#include "Customer.h"

Customer::Customer(int horizont, float speed, std::vector<int> needList, std::vector<int> detectList)
{
	this->horizont = horizont;
	this->speed = speed;
	this->needList = needList;
	this->detectList = detectList;

	
}

Customer::Customer(QObject* parent, QVector<QPair<int, int>> aim)
{
    setParent(parent);

	aimList = aim;
    leavingBrush = Qt::black;
    /*allTimer = new QTimer();
    allTimer->setInterval(500);*/

    
        
    getPathBySeq();
}

void Customer::getPathBySeq()
{
    for (int i = 0; i < aimList.size() - 1; i++) {
        vector<MapCell> temp = astar->getPath(aimList[i].first, aimList[i].second, aimList[i + 1].first, aimList[i + 1].second);
        qDebug() << "path" << i + 1 << "get";
        int size_bf = path.size();
        if (i != 0) {
            path.resize(size_bf + temp.size() - 1);
            for (int j = 1; j < temp.size(); j++)
                path[size_bf + j - 1] = temp[j];
        }
        else {
            path.resize(size_bf + temp.size());
            for (int j = 0; j < temp.size(); j++)
                path[size_bf + j] = temp[j];
        }

    }
}


void Customer::drawCell()
{
    if (leavingBrush != Qt::black) {
        leavingBrush = comingBrush;
    }
    else {
        //³õÊ¼
        x = path[0].x;
        y = path[0].y;
        x_before = x;
        y_before = y;
        leavingBrush = mapPanel->items[x - 1][y - 1]->brush();
        comingBrush = leavingBrush;
        mapPanel->items[x - 1][y - 1]->setBrush(Qt::red);
        mapPanel->update();
        return;
    }


    x_before = x;
    y_before = y;


    if (count_timer == path.size() - 1) {
        
    }  
    else {
        count_timer++;
        x = path[count_timer].x;
        y = path[count_timer].y;
    }

    comingBrush = mapPanel->items[x - 1][y - 1]->brush();
    mapPanel->items[x - 1][y - 1]->setBrush(Qt::red);
    mapPanel->items[x_before - 1][y_before - 1]->setBrush(leavingBrush);

    
}

void Customer::setConnectConfig()
{

}

void Customer::setThreadPool(QThreadPool* pThreadPool)
{
    threadPool = pThreadPool;
}

QVector<MapCell> Customer::getPath()
{
    return path;
}

void Customer::CustomerTask::writePath()
{

}
