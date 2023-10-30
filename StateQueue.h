#pragma once

#include <QState>

class StateQueue  : public QState
{
	Q_OBJECT

public:
	StateQueue(QObject *parent);
	~StateQueue();
};
