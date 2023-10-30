#include "StateFetch.h"

StateFetch::StateFetch(QObject *parent)
{
	setParent(parent);

}

StateFetch::~StateFetch()
{
	QEvent* e = new QEvent(QEvent::Type::User);

}
