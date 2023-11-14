#include "Clerk.h"

Clerk::Clerk(QObject *parent)
	: QObject(parent)
{
	m_machine = new ClerkMachine(this);

	willSlack = false;
	willRest = false;

	//��������Ҫ�����
	slackTime = 10000;
	restTime = 10000;
	m_workAction = ClerkAction::MOVE;
	
}

Clerk::~Clerk()
{}

void Clerk::createCart()
{
	cart = new Cart(this);
	
}

int Clerk::slackTime = 0;
int Clerk::restTime = 0;