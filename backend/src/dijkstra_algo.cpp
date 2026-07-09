#include<iostream>
#include <unordered_map>
#include<list>
#include<stack>
#include <limits> 
#include<queue>
#include<vector>

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
public: unordered_map<City*,list<pair<City*, Road*>>> adjacency;
};




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


int main(){

    unordered_map<City*,list<pair<City*,Road*>>> adjecency_list;
   // create cities
    City* a = new City{"A"};
    City* b = new City{"B"};
    City* c = new City{"C"};
    City* f = new City{"F"};

    // create roads
    Road* ab = new Road{10.0, 1.0, {true, "open"}};
    Road* ac = new Road{1.0,  1.0, {true, "open"}};
    Road* cb = new Road{1.0,  1.0, {true, "open"}};
    Road* bf = new Road{1.0,  1.0, {true, "open"}};

    unordered_map<City*, list<pair<City*, Road*>>> adjacency_list;
    adjacency_list[a].push_back({b, ab});
    adjacency_list[a].push_back({c, ac});
    adjacency_list[c].push_back({b, cb});
    adjacency_list[b].push_back({f, bf});
    adjacency_list[f];

    vector<City*> path = dijkstra(a, f, adjacency_list);

    for(City* city : path)
        cout << city->name << " ";
    cout << endl;

}
