#include <iostream>
#include "picojson.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace picojson;

#include "Lane.h"
#include "Road.h"
#include "Map.h"

int main()
{
	Map map;
	map.load_data_from_file("map.json");
}
