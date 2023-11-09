#include "UserRunningData.h"

UserRunningData::UserRunningData(QObject *parent)
	: QObject(parent)
{
	//��ȡ�ļ�����ʼ����������д��
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
