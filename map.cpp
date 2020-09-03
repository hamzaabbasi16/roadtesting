#include <iostream>
#include "picojson.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace picojson;
class Lane
{
	float id;
	float left_boundary_id;
	float right_boundary_id;
	std::vector<std::vector<double>> centre_point;
public:
   Lane(float Id, float Left_boundary_id, float Right_boundary_id, std::vector<std::vector<double>> cp){
        id = Id;
        left_boundary_id = Left_boundary_id;
        right_boundary_id = Right_boundary_id;
        centre_point = cp;
 }
};

class Road
{
	float id;
	float left_boundary_id;
	float right_boundary_id;
	std::vector<Lane> lanes;
public:
    Road(float Id, float Left_boundary_id, float Right_boundary_id, std::vector<Lane> rp)
    {
     id = Id;
     left_boundary_id = Left_boundary_id;
     right_boundary_id = Right_boundary_id;
     lanes = rp;
    }
};

class Map
{
	std::vector<Road> roads_;
public:
	void load_data_from_file(std::string file_name);
};

void Map :: load_data_from_file(std::string file_name)
{
	// pre processing
	std::ifstream f(file_name); //taking file as inputstream
	std::string json;
	if(f)
	{
		std::ostringstream ss;
	  	ss << f.rdbuf(); // reading data
	  	json = ss.str();
	}
	picojson::value v;
	std::string err;
	picojson::parse(v, json.c_str(), json.c_str() + strlen(json.c_str()), &err);
	if (!err.empty())
	{
		std::cerr << err << std::endl;
	}
	auto all_roads = v.get("roads").get<array>();
	for(int i=0; i<2; i++)
	{
		//Road road;
	  	auto all_lanes = all_roads[i].get("lanes").get<array>();

	  	std::vector<Lane> l;

    		for(int j=0; j<2; j++)
    		{
			//Lane lane;
			float id;
	        std::vector<std::vector<double>> centre_point;
			std::vector<double> tmp_points;
			std::vector<std::vector<double>> vec;
			auto all_points = all_lanes[j].get("centre_point").get<array>();
      			for(int k=0; k<720; k++)
      			{
				tmp_points.push_back(all_points[k].get<array>()[0].get<double>());
		  		tmp_points.push_back(all_points[k].get<array>()[1].get<double>());
                vec.push_back(tmp_points);
      			}
			float set_id = (all_lanes[j].get("id").get<double>());
			float set_left_boundary_id= (all_lanes[j].get("left_boundary_id").get<double>());
			float set_right_boundary_id = (all_lanes[j].get("right_boundary_id").get<double>());
      		Lane lane(set_id,set_left_boundary_id,set_right_boundary_id, vec);
            l.push_back(lane);

		 }
        std::vector<double> rd;
		float set_id = ( all_roads[i].get("id").get<double>() );
	   	float set_left_boundary_id = ( all_roads[i].get("left_boundary_id").get<double>() );
	   	float set_right_boundary_id = ( all_roads[i].get("right_boundary_id").get<double>() );
	   	Road road{set_id,set_left_boundary_id,set_right_boundary_id, l};
        roads_.push_back(road);
	 }
 }

int main()
{
	Map map;
	map.load_data_from_file("map.json");
}
