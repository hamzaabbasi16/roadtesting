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
struct Lane
{
	float id;
	float left_boundary_id;
	float right_boundary_id;
	std::vector<std::vector<double>> centre_point;
};
struct Road
{
	float id;
	float left_boundary_id;
	float right_boundary_id;
	std::vector<Lane> lanes;
};
class Map
{
	std::vector<Road> roads_;
public:
	void load_data_from_file(std::string file_name);
	float get_road2_id(){return roads_[0].lanes[0].centre_point[0][1];}
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
             for(int j=0; j<2; j++)
             {
		Lane lane;
		std::vector<double> tmp_points;
		auto all_points = all_lanes[j].get("centre_point").get<array>();
                for(int k=0; k<720; k++)
                {
		  tmp_points.push_back(all_points[k].get<array>()[0].get<double>());
		  tmp_points.push_back(all_points[k].get<array>()[1].get<double>());
		  lane.centre_point.push_back(tmp_points);
                }
		lane.id = all_lanes[j].get("id").get<double>();
		lane.left_boundary_id = all_lanes[j].get("left_boundary_id").get<double>();
		lane.right_boundary_id = all_lanes[j].get("right_boundary_id").get<double>();
                // fill other lane data
                road.lanes.push_back(lane);
             }
	     road.id =  all_roads[i].get("id").get<double>();
	     road.left_boundary_id = all_roads[i].get("left_boundary_id").get<double>();
	     road.right_boundary_id = all_roads[i].get("right_boundary_id").get<double>();	
	     // fill other road data	
             roads_.push_back(road);
         }
}

int main()
{
	Map map;
	map.load_data_from_file("map.json");
	std :: cout << map.get_road2_id();
	
}
