#include "Road.h"

Road :: Road(float a, float b, float c, std::vector<Lane> d)
{
	id = a;
	left_boundary_id = b;
	right_boundary_id = c;
	lanes = d;
}
