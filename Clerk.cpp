#include "Clerk.h"

Clerk::Clerk(QObject *parent)
	: QObject(parent)
{
	m_machine = new ClerkMachine(this);

	willSlack = false;
	willRest = false;

	//下面是需要读表的
	slackTime = 10000;
	restTime = 10000;
	m_workAction = ClerkAction::MOVE;
	m_AIData.stamina = 11000;

}

Clerk::~Clerk()
{}

void Clerk::createCart()
{
	cart = new Cart(this);
	
}

bool Clerk::staminaChange(const int& change)
{
	QMutexLocker(&staminaMutex);

	if (m_AIData.stamina + change <= 0) {
		m_AIData.stamina = 0;
		return true;
		
	}	
	else
		m_AIData.stamina += change;

	return false;
	
}

int Clerk::slackTime = 0;
int Clerk::restTime = 0;