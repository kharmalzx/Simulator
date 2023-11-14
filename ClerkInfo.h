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
	//first是下限，second是上限
	QPair<int, int> slackRandom;
	int shiftFactor;
	int moveSpeed;
	int loadSpeed;
};

struct ReplenishInfo {
	int facilitySn;

};