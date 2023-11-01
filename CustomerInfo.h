#pragma once
#include "MapPanel.h"
#include "StoreManage.h"
#include <qvector.h>

struct CommodityNeed {
	int commoditySn;
	int num_require;
};


struct CustomerAIData
{
	int id;
	int horizont;
	float speed;
	int num_tolerance;
	int waitWill;
	int t_total_patience;
	int t_wait_patience;
	float coefficient_checkout;
	float coefficient_service;
	float coefficient_fetch;
	

	QVector<CommodityNeed> list_commodity_needs;

};

struct StoreKnowledge
{
	Map* map;
	MapPanel* mapPanel;
	StoreManage* storeManage;
};

struct QueueInfo {
	bool isQueue;
	int facilitySn;
	MapCell* fetchPoint;
	int isInQueue1;
};

