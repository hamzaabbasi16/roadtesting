#include "Lane.h"

Lane :: Lane(float a, float b, float c, std::vector<std::vector<double>> d)
{
	id = a;
	left_boundary_id = b;
	right_boundary_id = c;
	centre_point = d;
}
