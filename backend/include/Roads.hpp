#pragma once 
#include"City.hpp"
#include<bits/stdc++.h>
using namespace std; 
class Road 
{
    public: 
        string name; 
        City* source;
        City* destination; 
        float distance; 
        float trafficFactor; 
        pair <bool, string> flags; 

        float getEstimatedTime(); 
        Road(string name, City* source, City *destination, float distance, float trafficFactor); 
        ~Road(); 



}; 