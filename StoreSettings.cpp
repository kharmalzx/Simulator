#include "StoreSettings.h"

StoreSettings::StoreSettings(QObject *parent)
	: QObject(parent)
{
	m_maxCount_trash = 5;
	list_trashPossiLoc.resize(m_maxCount_trash);
	m_solicitStamina = 3000;

}

StoreSettings::~StoreSettings()
{}
