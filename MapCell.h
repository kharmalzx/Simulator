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
	CELL_SOLICITAREA,
	CELL_DESTROY,
};


class MapCell
{
	
public:

	CellType type;
	
	MapCell* parent;  //只有1个最优的parent

	using pos = QPair<int, int>;
	//一环，左到右，上到下的8个点
	static const QVector<pos> circle_one;
	
	MapCell();

	void clear();
	bool isAccessible();
	bool isOccupied();
	void setOccupy(bool oc);
	static const pos getCircleOnePos(int index){	return circle_one[index]; }

	int x() const { return x_; };
	int y() const { return y_; };
	void setX(int x) { x_ = x; };
	void setY(int y) { y_ = y; };
	void setPos(int x, int y) { x_ = x; y_ = y; };
	float F() const { return F_; };
	float G() const { return G_; };
	float H() const { return H_; };
	void setF(float F) { F_ = F; };
	void setG(float G) { G_ = G; };
	void setH(float H) { H_ = H; };

private:
	int x_, y_;
	float F_, G_, H_;  //F=G+H
	//被其它人占用
	bool isOccupy;
};

