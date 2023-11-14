#pragma once

#include <QObject>

class Cart  : public QObject
{
	Q_OBJECT

public:
	Cart(QObject *parent);
	~Cart();

	void setSize(int size) { m_size = size; };
	int getSize() { return m_size; };

private:
	int m_size;
};
