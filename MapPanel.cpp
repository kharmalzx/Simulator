#include "MapPanel.h"

MapPanel::MapPanel(QObject *parent,Data* d)
	: QGraphicsScene(parent)
{

	this->data = d;
	map = data->map;



}

void MapPanel::updateMap() {
    this->update();
}

void MapPanel::drawMap()
{
    for (int i = 0; i < map->mapCells.size(); i++) {
        QVector<QGraphicsRectItem*> line;
        for (int j = 0; j < map->mapCells[i].size(); j++)
        {
            QGraphicsRectItem* item = new QGraphicsRectItem();
            item->setRect(j * 20, i * 20, 20, 20);
            if (map->mapCells[i][j].type == CellType::CELL_ACCESSIBLE)
                item->setBrush(QBrush(Qt::cyan));
            else if (map->mapCells[i][j].type == CellType::CELL_BLOCK)
                item->setBrush(QBrush(Qt::black));
            else if (map->mapCells[i][j].type == CellType::CELL_SHELF)
                item->setBrush(QBrush(Qt::yellow));
            else if (map->mapCells[i][j].type == CellType::CELL_FETCH)
                item->setBrush(QBrush(Qt::white));
            else if (map->mapCells[i][j].type == CellType::CELL_EXIT)
                item->setBrush(QBrush(Qt::blue));
            else if (map->mapCells[i][j].type == CellType::CELL_ENTRANCE)
                item->setBrush(QBrush(QColor(128, 0, 128)));
            addItem(item);
            line.push_back(item);
        }
        items.push_back(line);
    }

    
}
