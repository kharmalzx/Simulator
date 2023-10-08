#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Simulator.h"
#include "Customer.h"
#include "StoreManage.h"
#include "MapPanel.h"

using std::shared_ptr;

class Simulator : public QMainWindow
{
    Q_OBJECT

public:
    Simulator(QWidget *parent = nullptr);

private:
    Ui::SimulatorClass ui;
    Data* data;
    Map* map;
    MapPanel* mapPanel;
    QGraphicsView* view;
    
    AStarPathfinding* astar;
    
    vector<MapCell> path;
    QTimer* timer;
    StoreManage* storeManage;
    void drawMap();

    int x_before;
    int y_before;
    int x;
    int y;
    int count_timer = 0;
    QBrush comingBrush;
    QBrush leavingBrush;

private slots:
    
};
