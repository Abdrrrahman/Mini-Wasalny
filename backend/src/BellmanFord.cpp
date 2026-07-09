#include<iostream>
#include<unordered_map>
#include<list>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class City 
{
    public:
    string name;
};

class Road
{
    public:
    double distance;
    float trafficFactor;
    pair<bool, string> status;
};

class Map
{
    public:
    unordered_map<City*, list<pair<City*, Road*>>> adjancency;
};

vector<City*> BellmanFord(unordered_map<City*, list<pair<City*, Road*>>>& graph, City *source, City *destination)
{
    unordered_map<City*, double> distance;
    unordered_map<City*, City*> parent;

    for(auto& city : graph)
    {
        distance[city.first] = 1e8;

        for(auto& neighbor : city.second)
            distance[neighbor.first] = 1e8;
    }

    distance[source] = 0;
    int cities = graph.size();

    for(int i = 0; i < cities; i++)
    {
        bool updated = false;
        for(auto& city : graph)
        {
            City* current = city.first;

            for(auto& neighbor : city.second)
            {
                City* next = neighbor.first;
                Road* road = neighbor.second;

                if(road->status.first) // skipping closed roads
                    continue;

                double weight = road->distance * road->trafficFactor;

                if(distance[current] != 1e8 && distance[current] + weight < distance[next])
                {
                    distance[next] = distance[current] + weight;
                    parent[next] = current;
                    updated = true;

                    if(i == cities - 1)
                        return {}; // Negative weight cycle detected
                }
            }
        }

        if(!updated)
            break;
    }

    vector<City*> path;

    if(distance[destination] == 1e8)
        return path;

    City* current = destination;

    while(current != source)
    {
        if(parent.find(current) == parent.end()) // in case a city is isolated
            return {};

        path.push_back(current);
        current = parent[current];
    }

    path.push_back(source);
    reverse(path.begin(), path.end());

    return path;
}