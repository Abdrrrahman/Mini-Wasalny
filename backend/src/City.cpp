#include"../include/City.hpp" 

City::City(string name, int cities_num ,int id,float x, float y, string description)
{
    this-> name = name; 
    this->cities_num= cities_num; 
    this-> coordinates = {x,y}; 
    this->description = description ; 
    this->id = id; 
}
City::City()
    {
        ++cities_num;
        id = cities_num;      
        g = 0.0;
        h = 0.0;
        f = 0.0;
        coordinates.first = 0.0;
        coordinates.second = 0.0;
    }