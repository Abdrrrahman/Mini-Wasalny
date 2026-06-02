#include"../include/Roads.hpp" 
Road::Road(string name, City* source, City* destination, float distance, float trafficFactor)
{
    this-> name = name; 
    this-> source = source; 
    this-> destination= destination; 
    this-> distance = distance; 
    this-> trafficFactor=  trafficFactor; 
    this-> flags = {false, " "}; 

}

Road::~Road()
{
    
}