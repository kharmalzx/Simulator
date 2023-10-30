#pragma once

#include <QState>
#include <QEvent>

class StateFetch  : public QState
{
	Q_OBJECT

public:
	StateFetch(QObject *parent);
	~StateFetch();
};
