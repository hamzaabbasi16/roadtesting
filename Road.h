#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include "Lane.h"

class Road
{
	float id;
	float left_boundary_id;
	float right_boundary_id;
	std::vector<Lane> lanes;
public:
	Road(float a, float b, float c, std::vector<Lane> d);
	float get_id(){return id;}
	float get_left_boundary_id(){return left_boundary_id;}
	float get_right_boundary_id(){return right_boundary_id;}
	std::vector<Lane> get_lanes(){return lanes;}

};

#endif
