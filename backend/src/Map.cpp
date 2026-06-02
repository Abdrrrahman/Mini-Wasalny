#include"../include/Map.hpp"
Map::Map(string name)
{
    this->name = name; 
}



Map::~Map()
{
    for (City* c : cities) delete c;
    for (Road* r : roads) delete r;
}