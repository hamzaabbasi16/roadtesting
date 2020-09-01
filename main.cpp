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
struct Map
{
	std::vector<Road> roads;
};
int main()
{
	// pre processing
	std::ifstream f("map.json"); //taking file as inputstream
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
	 
	// ********** Loading Lane 1 data**************
	Lane lane_1;
	lane_1.id =  v.get("roads").get<array>()[0].get("lanes").get<array>()[0].get("id").get<double>();
	lane_1.left_boundary_id = v.get("roads").get<array>()[0].get("lanes").get<array>()[0].get("left_boundary_id").get<double>();
	lane_1.right_boundary_id = v.get("roads").get<array>()[0].get("lanes").get<array>()[0].get("right_boundary_id").get<double>();
	
	for(int i = 0; i < 720; i++)
	{	std::vector<double> vec;
	       	auto json_point = v.get("roads").get<array>()[0].get("lanes").get<array>()[0].get("centre_point").get<array>()[i];
		vec.push_back(json_point.get<array>()[0].get<double>());
		vec.push_back(json_point.get<array>()[1].get<double>());
		//std::cout<<"x: "<<vec[0]<<", y: "<<vec[1]<<std::endl;
		lane_1.centre_point.push_back(vec);
	}
	// ********** Loading Lane 2 data**************
	Lane lane_2;
	lane_2.id =  v.get("roads").get<array>()[0].get("lanes").get<array>()[1].get("id").get<double>();
	lane_2.left_boundary_id = v.get("roads").get<array>()[0].get("lanes").get<array>()[1].get("left_boundary_id").get<double>();
	lane_2.right_boundary_id = v.get("roads").get<array>()[0].get("lanes").get<array>()[1].get("right_boundary_id").get<double>();
	
	for(int i = 0; i < 720; i++)
	{	std::vector<double> vec;
	       	auto json_point = v.get("roads").get<array>()[0].get("lanes").get<array>()[1].get("centre_point").get<array>()[i];
		vec.push_back(json_point.get<array>()[0].get<double>());
		vec.push_back(json_point.get<array>()[1].get<double>());
		//std::cout<<"x: "<<vec[0]<<", y: "<<vec[1]<<std::endl;
		lane_2.centre_point.push_back(vec);
	}
	// ********** Loading Lane 3 data**************
	Lane lane_3;
	lane_3.id =  v.get("roads").get<array>()[1].get("lanes").get<array>()[0].get("id").get<double>();
	lane_3.left_boundary_id = v.get("roads").get<array>()[1].get("lanes").get<array>()[0].get("left_boundary_id").get<double>();
	lane_3.right_boundary_id = v.get("roads").get<array>()[1].get("lanes").get<array>()[0].get("right_boundary_id").get<double>();
	
	for(int i = 0; i < 720; i++)
	{	std::vector<double> vec;
	       	auto json_point = v.get("roads").get<array>()[1].get("lanes").get<array>()[0].get("centre_point").get<array>()[i];
		vec.push_back(json_point.get<array>()[0].get<double>());
		vec.push_back(json_point.get<array>()[1].get<double>());
		//std::cout<<"x: "<<vec[0]<<", y: "<<vec[1]<<std::endl;
		lane_3.centre_point.push_back(vec);
	}
	// ********** Loading Lane 4 data**************
	Lane lane_4;
	lane_4.id =  v.get("roads").get<array>()[1].get("lanes").get<array>()[1].get("id").get<double>();
	lane_4.left_boundary_id = v.get("roads").get<array>()[1].get("lanes").get<array>()[1].get("left_boundary_id").get<double>();
	lane_4.right_boundary_id = v.get("roads").get<array>()[1].get("lanes").get<array>()[1].get("right_boundary_id").get<double>();
	
	for(int i = 0; i < 720; i++)
	{	std::vector<double> vec;
	       	auto json_point = v.get("roads").get<array>()[1].get("lanes").get<array>()[1].get("centre_point").get<array>()[i];
		vec.push_back(json_point.get<array>()[0].get<double>());
		vec.push_back(json_point.get<array>()[1].get<double>());
		//std::cout<<"x: "<<vec[0]<<", y: "<<vec[1]<<std::endl;
		lane_4.centre_point.push_back(vec);
	}

	// ********** Loading the lanes to the road structure ***********

	// ********** Loading Road 1 Structure ***************
	Road road_1;
	road_1.id =  v.get("roads").get<array>()[0].get("id").get<double>();
	road_1.left_boundary_id = v.get("roads").get<array>()[0].get("left_boundary_id").get<double>();
	road_1.right_boundary_id = v.get("roads").get<array>()[0].get("right_boundary_id").get<double>();
	road_1.lanes.push_back(lane_1);
	road_1.lanes.push_back(lane_2);
	// ********** Loading Road 2 Structure ***************
	Road road_2;
	road_2.id =  v.get("roads").get<array>()[1].get("id").get<double>();
	road_2.left_boundary_id = v.get("roads").get<array>()[1].get("left_boundary_id").get<double>();
	road_2.right_boundary_id = v.get("roads").get<array>()[1].get("right_boundary_id").get<double>();
	road_2.lanes.push_back(lane_3);
	road_2.lanes.push_back(lane_4);


	// ************ Loading the roads to the map structure **********
	
	Map map;
	map.roads.push_back(road_1);
	map.roads.push_back(road_2);

}
