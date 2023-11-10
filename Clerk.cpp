#include "Clerk.h"

Clerk::Clerk(QObject *parent)
	: QObject(parent)
{
	m_machine = new ClerkMachine(this);

}

Clerk::~Clerk()
{}
