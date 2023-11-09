#include "UserRunningData.h"

UserRunningData::UserRunningData(QObject *parent)
	: QObject(parent)
{
	//读取文件，初始化，现在先写死
	money = 0;
}

UserRunningData::~UserRunningData()
{}


void UserRunningData::reduceMoney(long long money)
{
	QMutexLocker locker(&moneyChangeMutex);

	if (this->money >= money) {
		this->money -= money;
	}
	else
		qDebug("UserRunningData::reduceMoney(long long money) money is not enough");
}

void UserRunningData::addMoney(long long money)
{
	QMutexLocker locker(&moneyChangeMutex);

	this->money += money;
}
