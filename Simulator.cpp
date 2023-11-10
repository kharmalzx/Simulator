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

    storeManage->startSimulation();
}

void Simulator::drawMap()
{

    mapPanel->drawMap();
    view->show();
}
