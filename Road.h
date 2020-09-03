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
Road :: Road(float a, float b, float c, std::vector<Lane> d)
{
	id = a;
	left_boundary_id = b;
	right_boundary_id = c;
	lanes = d;
}
