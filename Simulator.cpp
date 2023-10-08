#include "Simulator.h"

Simulator::Simulator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    astar = new AStarPathfinding();
    astar->readMap();
    data = astar->data;
    map = data->map;

    view = new QGraphicsView();
    mapPanel = new MapPanel(view, data);   
    view->setScene(mapPanel);

    storeManage = new StoreManage(this,mapPanel,astar);

    drawMap();


    QVector<QPair<int, int>> aimList;
    
    aimList.push_back(QPair<int, int>(map->entranceArea[0].x, map->entranceArea[0].y));
    aimList.push_back(QPair<int, int>(6, 16));
    aimList.push_back(QPair<int, int>(14, 25));
    aimList.push_back(QPair<int, int>(map->exitArea[0].x, map->exitArea[0].y));

    storeManage->createCustomer(aimList);

    aimList.clear();
    aimList.push_back(QPair<int, int>(map->entranceArea[1].x, map->entranceArea[1].y));
    aimList.push_back(QPair<int, int>(4, 11));
    aimList.push_back(QPair<int, int>(8, 29));
    aimList.push_back(QPair<int, int>(map->exitArea[1].x, map->exitArea[1].y));
    storeManage->createCustomer(aimList);


    storeManage->startSimulation();
}

void Simulator::drawMap()
{

    mapPanel->drawMap();
    view->show();
}
