#include "Data.h"

Data::Data()
{
	map = new Map();

}

template<typename T>
inline T Data::get(DataType req_type, int groupID)
{
	switch (req_type)
	{
	default:
		break;
	}
	return T();
}

Data::~Data() {
	delete map;
}