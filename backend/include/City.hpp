#pragma once 
#include<bits/stdc++.h>
using namespace std; 

struct vector2
{
    float x, y; 
}; 

class City
{
  public: 
    list<City*> neighboors; 
    string name; 
    int cities_num; 
    int id; 
    float g; 
    float h; 
    float f; 

    City* parent; 
    pair<float,float> coordinates;
    vector2 velocity; 
    vector2 force; 
    string description; 
    City();  
    City (string name, int cities_num,int id,float x, float y, string description);
    ~City(); 

}; 