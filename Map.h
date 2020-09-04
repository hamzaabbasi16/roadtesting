#ifndef MAP_H
#define MAP_H

#include "Road.h"
#include <vector>
#include <string>


class Map
{
	std::vector<Road> roads_;
public:
	void load_data_from_file(std::string file_name);
};

#endif
