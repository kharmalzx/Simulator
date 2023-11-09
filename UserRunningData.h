#pragma once

#include <QObject>
#include <qmutex.h>
#include "ExcelTool.h"

class UserRunningData  : public QObject
{
	Q_OBJECT

public:
	UserRunningData(QObject *parent);
	~UserRunningData();

	void readData(ExcelTool* tool);

	void reduceMoney(long long money);
	void addMoney(long long money);
	
private:

	long long money;

	QMutex moneyChangeMutex;

};
