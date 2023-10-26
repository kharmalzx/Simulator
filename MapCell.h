#pragma once
#include <qvector.h>
#include <qobject.h>

enum CellType
{
	CELL_BLOCK,
	CELL_ACCESSIBLE,
	CELL_FETCH,
	CELL_SHELF,
	CELL_COMPLEX,
	CELL_DRESSINGROOM,
	CELL_CASHIER,
	CELL_STOREHOUSE,
	CELL_STAFFROOM,
	CELL_EXIT,
	CELL_ENTRANCE,
	CELL_SERVICE_PORTS,
};


class MapCell
{
	
public:

	int x, y;
	CellType type;
	float F, G, H;  //F=G+H
	MapCell* parent;  //ֻ��1�����ŵ�parent

	using pos = QPair<int, int>;
	//һ�������ң��ϵ��µ�8����
	static const QVector<pos> circle_one;
	
	

	MapCell();

	void clear();
	bool isAccessible();
	bool isOccupied();
	void setOccupy(bool oc);
	static const pos getCircleOnePos(int index){	return circle_one[index]; }

private:

	//��������ռ��
	bool isOccupy;
};

