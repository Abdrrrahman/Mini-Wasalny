#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;




class city
{
    // node Neighbors; // (city — city ) → list
    public:
    // 
    static int cities_num;
    int id;
    float g;
    float h;
    float f;
    city * parent;
    // 
    pair<float,float> coordinates; //→ (x, y)
    
    city()
    {
        ++cities_num;
        id = cities_num;      
        g = 0.0;
        h = 0.0;
        f = 0.0;
        coordinates.first = 0.0;
        coordinates.second = 0.0;
    }
};

int city::cities_num = 0;

vector<city> reconstruct_path(const city *end);
float Heuristic(const pair<float,float>& origin,const pair<float,float>& des);

class road
{
    // node Neighbors; // (city — city ) → list
    public:
        city* source;
        city* destination;
        float time;        
        road()
        {
            source = NULL;
            destination = NULL;
            time = 0.0;
        }
            
};


vector<city> shortestPathAstar(const city& origin,const city& destination ,unordered_map<int,vector<pair<city,road>>>& adj)
{

    vector<city> openList;
    vector<city> closedList;
    closedList.reserve(5000);

    city start = origin;
    start.g = 0;
    start.h = Heuristic(origin.coordinates,destination.coordinates);
    start.f = start.h + start.g;
    start.parent =NULL;
    openList.push_back(start);
    
    while(openList.size() != 0)
    {
        // gets the node with least f 
        int index = 0;
        for( int i = 1; i < openList.size();++i)
        {
            if(openList[i].f < openList[index].f)
                index = i;
        }
        
        city current = openList[index]; // local variable 

        
        // checking if the current node is the destination 
        if(current.id == destination.id)
        {
            closedList.push_back(current);
            return reconstruct_path(&closedList.back()); 
        }
        
        // moving the node from open list to closed list *evaluated* 
        closedList.push_back(openList.at(index));
        openList.erase(openList.begin() + index);
        
        // checking neighbors of current node and checking if it is evaluated or not     
        
        
        // it needs lots of improvements 
        for(auto& [neighbor,road] : adj[current.id])
        {   
            bool checkingClosedlist =0;
            for(int i = 0 ; i < closedList.size(); ++i)
            {
                if(closedList[i].id == neighbor.id)
                {
                    checkingClosedlist = 1;
                    break;
                }
            }
            
            float tentative_g = current.g + road.time;

            // checking if the neighbor is in openList to avoid duplicates  
            int checkingOpenedlist = -1;
            for(int i = 0 ; i < openList.size(); ++i)
            {
                if(openList[i].id == neighbor.id)
                {
                    checkingOpenedlist = i;
                    break;
                }
            }

            if(checkingClosedlist == 0 && checkingOpenedlist == -1) // when checkingOpenedlist = 0 and checkingClosedlist = 0 return true
            {
                neighbor.g = tentative_g;
                neighbor.h = Heuristic(neighbor.coordinates,destination.coordinates);
                neighbor.f = neighbor.g + neighbor.h;
                neighbor.parent = &openList.back();
                openList.push_back(neighbor);
            }
            else if(checkingOpenedlist != -1)
            {
                if(tentative_g < neighbor.g)
                {
                    openList[checkingOpenedlist].g = tentative_g;
                    openList[checkingOpenedlist].h = Heuristic(openList[checkingOpenedlist].coordinates,destination.coordinates);
                    openList[checkingOpenedlist].f = openList[checkingOpenedlist].g + openList[checkingOpenedlist].h;
                    openList[checkingOpenedlist].parent = &closedList.back(); // address of the last element in the vector 
                }
            }
        }
    }    
    
    return {}; // empty vector
}


vector<city> reconstruct_path(const city *end)
{
    vector <city> path;
    
    while(end != NULL)
    {
        path.push_back(*end);
        end = end->parent;
    }
    return path;
}

float Heuristic(const pair<float,float>& origin,const pair<float,float>& des)
{
    float x = origin.first - des.first;
    float y = origin.second - des.second;
    return abs(x) + abs(y);
}
