#pragma once 
#include <bits/stdc++.h>
#include "City.hpp"
#include "Roads.hpp"

using namespace std; 
class Map
{

    public: 
        string name; 
        list<City*> cities; 
        list<Roads*> roads; 
        list<pair<City* , Roads*>> adjacencyList; 

        Map(string name); 
        ~Map(); 

        void addCity(City* city); 
        void deleteCity(City* City); 
        void editCity( City* city);

        void addRoad(Roads* road); 
        void deleteRoad (Roads* road); 
        void editRoad (Roads* road); 
        vector<City*> find_shortest_path (City* source, City* destination); 
        float Time_estimated_for_path (vector<City*> chosen_path); 

        //adjacency list getter
        list<pair<City*, Roads*>> getAdjacencylist(); 
        // getter for cities (Searching). 
        list<City*> getCities(); 



}; 