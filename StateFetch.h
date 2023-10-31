#pragma once

#include "AbstractCustomerState.h"

class StateFetch  : public AbstractCustomerState
{
	Q_OBJECT

public:
	StateFetch(QObject *parent);
	~StateFetch();
};
