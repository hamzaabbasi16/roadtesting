#include <iostream>
#include "picojson.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

//using namespace std;
using namespace picojson;
// example json object reading code
class Lane
{
	float id;
	float left_boundary_id;
	float right_boundary_id;
	std::vector<std::vector<double>> centre_point;
public:
	void set_id(float a){id = a;}
	void set_left_boundary_id(float a){left_boundary_id = a;}
	void set_right_boundary_id(float a){right_boundary_id = a;}
	void set_centre_point(std::vector<std::vector<double>> a){centre_point = a;}
	float get_id(){return id;}
	float get_left_boundary_id(){return left_boundary_id;}
	float get_right_boundary_id(){return right_boundary_id;}	
	std::vector<std::vector<double>> get_centre_point(){return centre_point;}
};
class Road
{
	float id;
	float left_boundary_id;
	float right_boundary_id;
	std::vector<Lane> lanes;
public:
	void set_id(float a){id = a;}
	void set_left_boundary_id(float a){left_boundary_id = a;}
	void set_right_boundary_id(float a){right_boundary_id = a;}
	void set_lanes(std::vector<Lane> a){lanes = a;}
	float get_id(){return id;}
	float get_left_boundary_id(){return left_boundary_id;}
	float get_right_boundary_id(){return right_boundary_id;}	
	std::vector<Lane> get_lanes(){return lanes;}
};
class Map
{
	std::vector<Road> roads_;
public:
	void load_data_from_file(std::string file_name);
	
	float get_r1_l1_l_b_id(){return roads_[0].get_lanes()[0].get_left_boundary_id();}
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
             Road road;
	     auto all_lanes = all_roads[i].get("lanes").get<array>();
	     std::vector<Lane> l;
             for(int j=0; j<2; j++)
             {
		Lane lane;
		std::vector<double> tmp_points;
		std::vector<std::vector<double>> vec;
		auto all_points = all_lanes[j].get("centre_point").get<array>();
                for(int k=0; k<720; k++)
                {
		  tmp_points.push_back(all_points[k].get<array>()[0].get<double>());
		  tmp_points.push_back(all_points[k].get<array>()[1].get<double>());
		  vec.push_back(tmp_points);
                }
		lane.set_centre_point(vec);
		lane.set_id(all_lanes[j].get("id").get<double>());
		lane.set_left_boundary_id(all_lanes[j].get("left_boundary_id").get<double>());
		lane.set_right_boundary_id(all_lanes[j].get("right_boundary_id").get<double>());
                // fill other lane data
		l.push_back(lane);
             }
	     road.set_id( all_roads[i].get("id").get<double>() );
	     road.set_left_boundary_id( all_roads[i].get("left_boundary_id").get<double>() );
	     road.set_right_boundary_id( all_roads[i].get("right_boundary_id").get<double>() );	
	     road.set_lanes( l );
	     // fill other road data	
             roads_.push_back(road);
         }
}

int main()
{
	Map map;
	map.load_data_from_file("map.json");
	
}
