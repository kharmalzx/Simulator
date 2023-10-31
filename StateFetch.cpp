#include "StateFetch.h"

StateFetch::StateFetch(QObject *parent): AbstractCustomerState(parent)
{

}

StateFetch::~StateFetch()
{
	QEvent* e = new QEvent(QEvent::Type::User);

}
