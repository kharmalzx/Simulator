#pragma once

#include <QObject>
#include "ClerkInfo.h"
#include "ClerkMachine.h"

class Clerk  : public QObject
{
	Q_OBJECT

public:
	Clerk(QObject *parent);
	~Clerk();


private:
	ClerkMachine* m_machine;
	

};
