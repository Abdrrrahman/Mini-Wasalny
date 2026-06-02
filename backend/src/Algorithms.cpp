#include<bits/stdc++.h>
#include"../include/City.hpp"
#include"../include/Map.hpp"
#include"../include/Roads.hpp"

using namespace std; 

//Bassma
//A-star
vector<City> reconstruct_path(City *end);
float Heuristic(pair<float,float> origin, pair<float,float> des);
class road
{
    // node Neighbors; // (city — city ) → list
    public:
        City* source;
        City* destination;
        float time;        
        road()
        {
            source = NULL;
            destination = NULL;
            time = 0.0;
        }
            
};

vector<City> shortestPathAstar(City origin,City destination ,unordered_map<int,vector<pair<City,road>>> adj)
{

    vector<City> openList;
    vector<City> closedList;
    closedList.reserve(5000);
    vector <City> path;

    City start = origin;
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
        
        City current = openList[index]; // local variable 

        
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
    
    return path; // path is and empty vector
}


vector<City> reconstruct_path(City *end)
{
    vector <City> path;
    
    while(end != NULL)
    {
        path.push_back(*end);
        end = end->parent;
    }
    return path;
}

float Heuristic(pair<float,float> origin, pair<float,float> des)
{
    float x = origin.first - des.first;
    float y = origin.second - des.second;
    return abs(x) + abs(y);
}

//----------------------------------------------------


//BasicTraversal

//Check for the validations of the parameter list
//source : it is an option if the user wants to start from a specific city.
// if source is not provided so it will start from the begin of the graph which is not const bec. it's an unordered map.
bool isValid(const unordered_map<City*, list<pair<City*, Road*>>>& graph, City*& source) {
    if (graph.empty()) {
        cout << "Graph is empty!!!\n";
        return false;
    }
    if (source == nullptr) {
        source = graph.begin()->first;
    }
    else if (graph.find(source) == graph.end())
    {
        cout << "City \"" << source->name << "\" not found in graph.\n";
        return false;
    }
    return true;

}

void BFS(const unordered_map<City*, list<pair<City*, Road*>>>& graph,City* source= nullptr)
{
    if (!isValid(graph,source)) return;

    unordered_set<City*> visited;
    queue<City*> q;
    City* current;

    visited.insert(source);
    q.push(source);

    cout << "BFS: ";
    while (!q.empty()) {
        current = q.front();
        q.pop();
        if (graph.find(current) == graph.end()) continue;
        cout << current->name << "  ";

        for (auto it = graph.at(current).begin(); it != graph.at(current).end(); ++it)
        {
            City* neighbor = it->first;
            Road* road = it->second;
            if (neighbor == nullptr || road == nullptr) continue;

            if (road->flags.first) {
                cout << "\n[Skipped: " << road->name
                    << " is blocked - " << road->flags.second << "]\n";
                continue;
            }

            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    cout << "\n";
}


void DFS(const unordered_map<City*, list<pair<City*, Road*>>>& graph, City* source= nullptr) 
{
    if (!isValid(graph,source)) return;
   
    City* current;
    unordered_set<City*> visited;
    stack<City*> s;

    s.push(source);

    cout << "DFS: ";
    while (!s.empty()) {
        current = s.top();
        s.pop();
        if (graph.find(current) == graph.end()) continue;

        if (visited.find(current) == visited.end()) 
        {
            visited.insert(current);
            cout << current->name << "  ";

            for (auto it = graph.at(current).begin(); it != graph.at(current).end(); ++it)
            {
                City* neighbor = it->first;
                Road* road = it->second;

                if (neighbor == nullptr || road == nullptr) continue;

                if (road->flags.first) {
                    cout << "\n[Skipped: " << road->name
                        << " is blocked - " << road->flags.second << "]\n";
                    continue;
                }

                if (visited.find(neighbor) == visited.end()) {
                    s.push(neighbor);
                }
            }
        }
    }
    cout << "\n";
}

//----------------------------------------------------

//Bellman-Ford
vector<string> BellmanFord(unordered_map<City*, list<pair<City*, Road*>>>& graph, City *source, City *destination)
{
    unordered_map<City*, double> distance;
    unordered_map<City*, City*> parent;

    for(auto& city : graph)
    {
        distance[city.first] = 1e8; //cute way of saying infinity (could be changed later)

        for(auto& neighbor : city.second)
            distance[neighbor.first] = 1e8;
    }

    distance[source] = 0;
    int cities = graph.size();

    //Bellman-Ford with V iterations (supposed to be V-1, but bear with me, I have an idea)
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

                if(road->flags.first) //skipping closed roads 
                    continue;

                double weight = road->distance * road->trafficFactor;

                if(distance[current] != 1e8 && distance[current] + weight < distance[next])
                {
                    distance[next] = distance[current] + weight;
                    parent[next] = current;
                    updated = true;

                    if(i == cities - 1)
                        return {"Negative weight cycle detected"};
                }
            }
        }

        if(!updated)
            break;
    }

    vector<string> path;

    if(distance[destination] == 1e8)
        return path;

    City* current = destination;
    while(current != source)
    {
        if(parent.find(current) == parent.end()) //in case a city is isolated
            return {};

        path.push_back(current->name);
        current = parent[current];
    }

    path.push_back(source->name);
    reverse(path.begin(), path.end());

    return path;
}

//Doha
//Dijkistra
// for sorting in priority_queue
struct minimum_cost {
    bool operator()(pair<City*,double> p1, pair<City*,double> p2){
        return p1.second > p2.second;
    }
};

vector<City*> dijkstra(City* source, City* destination, unordered_map<City*, list<pair<City*, Road*>>> adjacency_list){

    unordered_map<City*, bool>   visit;
    unordered_map<City*, double> cost;
    unordered_map<City*, City*> prev;
    stack<City*> passed_cities;

    // or  double pos_inf = 1e9;
    double pos_inf = numeric_limits<double>::infinity();

   for(auto adj:adjacency_list){
    cost[adj.first]=pos_inf;
    visit[adj.first]=0;
    prev[adj.first]=nullptr;
    }

    // starting with source with cost 0 
    cost[source] = 0;

    priority_queue<pair<City*,double>, vector<pair<City*,double>>,minimum_cost> min;
    min.push({source, 0.0});

    while(!visit[destination]){

        if(min.empty()) break; 

        // get the minimum city of cost to see its neighbours
        City* this_node = min.top().first;
        min.pop();

        // if it was already visited then continue
        if(visit[this_node]) continue; 
        visit[this_node] = true;

        for(auto neighbour : adjacency_list[this_node]){
            if(!visit[neighbour.first]){
                //get the length from the start of the path till city
                double length = cost[this_node] + neighbour.second->distance;
                
                //update the cost if the length has smaller value
                if(length < cost[neighbour.first]){

                    cost[neighbour.first]  = length;
                    prev[neighbour.first]  = this_node;
                    min.push({neighbour.first, cost[neighbour.first]}); 

                }
            }
        }
    }

    // get the path first with stack because we are getting it backwards
    City* city = destination;
    while(city != source){

        passed_cities.push(city);

        if(prev[city] == nullptr){
        cout << "No path found" << endl;
        return {};
    }
        city = prev[city];
    }
    passed_cities.push(source);


    // put the stack in the vector
    vector<City*> path;
    while(!passed_cities.empty()){
        path.push_back(passed_cities.top());
        passed_cities.pop();
    }

    return path;
}