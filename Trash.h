#pragma once

#include <QObject>
#include "MapCell.h"

class Trash  : public QObject
{
	Q_OBJECT

public:
	Trash(QObject *parent);
	~Trash();

	void setIcon(QString icon) { m_icon = icon; }
	void setLoc(MapCell* loc) { m_loc = loc; }
	MapCell* locAt() { return m_loc; }
	void clean();


private:
	QString m_icon;
	MapCell* m_loc;
};
