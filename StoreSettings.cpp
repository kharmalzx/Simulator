#include "StoreSettings.h"

StoreSettings::StoreSettings(QObject *parent)
	: QObject(parent)
{
	maxCount_trash = 5;
	list_trashPossiLoc.resize(maxCount_trash);
	
}

StoreSettings::~StoreSettings()
{}
