#include "Map.h"
using namespace std;
int main()
{
	Map map;
	map.load_data_from_file("map.json");
   // map.get_road2_id();
    
	map.get_road_information(Position);

}
