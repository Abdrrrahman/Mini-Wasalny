#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct Road;

struct City {
    string name;
    list<pair<City*, Road*>> neighbors;
    pair<float, float> coordinates;
    string description;
};
struct Road {
    string name;
    City* source;
    City* destination;
    float distance;
    float trafficFactor;
    pair<bool, string> flag;
};

//Check for the validations of the parameter list
//source : it is an option if the user wants to start from a specific city.
// if source is not provided so it will start from the begin of the graph which is not const bec. it's an unordered map.
bool isValid(const unordered_map<City*, list<pair<City*, Road*>>>& graph, City* source) {
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

void BFS(const unordered_map<City*, list<pair<City*, Road*>>>& graph, City* source = nullptr)
{
    if (!isValid(graph, source)) return;

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

            if (road->flag.first) {
                cout << "\n[Skipped: " << road->name
                    << " is blocked - " << road->flag.second << "]\n";
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


void DFS(const unordered_map<City*, list<pair<City*, Road*>>>& graph, City* source = nullptr)
{
    if (!isValid(graph, source)) return;

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

                if (road->flag.first) {
                    cout << "\n[Skipped: " << road->name
                        << " is blocked - " << road->flag.second << "]\n";
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

int main() {

    return 0;
}