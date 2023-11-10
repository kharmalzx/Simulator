#pragma once

#include <QObject>

struct ClerkAIData
{
	int id;
	int star;
	int initialPosSn;
	QString icon;
	int stamina;
	int replenishSpeed;
	int serveSpeed;
	//first�����ޣ�second������
	QPair<int, int> slackRandom;
	int shiftFactor;
	int moveSpeed;
};

struct ReplenishInfo {
	int facilitySn;

};