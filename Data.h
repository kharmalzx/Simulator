#pragma once
#include "Map.h"


class Data
{
	enum DataType {
		AI,
	};

public:

	Data();
	~Data();

	Map* map;

	template<typename T>
	T get(DataType, int groupID);

};


