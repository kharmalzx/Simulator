#pragma once

#include <QObject>

class CharacterSettings  : public QObject
{
	Q_OBJECT

public:
	CharacterSettings(QObject *parent);
	~CharacterSettings();

	void setCartSize(const int& cartSize) { m_cartSize = cartSize; }
	int cartSize() const { return m_cartSize; }

private:
	int m_cartSize;
	QVector<int> eventPriority;
};
