#include <iostream>
#include <unordered_map>
#include<list>
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


enum Algorithm
{
	DIJKSTRA = 0,
	A_STAR = 1,
    BELLMANFORD=2
};

//to be able to cin enum
std::istream& operator>>( std::istream& is, Algorithm& i )
{
    int tmp ;
    if ( is >> tmp )
        i = static_cast<Algorithm>( tmp ) ;
    return is ;
}


void Choose_Algo(){
    
    // if all funtions are implemented the same way the source, destination and the returned vector will be declared once at first only and the loop of the vector will be after the if else 
    // for now i declared the source,destination and passed_cities vectors in each loop 


    Algorithm value;
    cout<<"Enter a number (0 for DIJKSTRA, 1 for A_STAR, 2 for BELLMANFORD): "<<endl;
    cin>>value;


    if(value==DIJKSTRA){
        cout<<"Choose source city: ";
        City* source= new City();
        City* destination= new City();
        cin>> source->name;
        cout<<"Choose destination city: ";
        cin>> destination->name;

        vector<City*> passed_cities;

        //passed_cities = dijkstra(source,destination,adjacency_list);

    }
    else if(value==A_STAR){
   
        cout<<"Choose source city: ";
        City source;
        City destination;
        cin>> source.name;
        cout<<"Choose destination city: ";
        cin>> destination.name;

        vector<City> passed_cities;

        // source, destination and returned vector are of city type unlike dijkstra is pointer to a city
        // passed_cities= shortestPathAstar(source,destination,adjacency_list);
 
    }
    else{
        cout<<"Choose source city: ";
        City* source= new City();
        City* destination= new City();
        cin>> source->name;
        cout<<"Choose destination city: ";
        cin>> destination->name;

        vector<string> passed_cities;

        //the vector returned is of type string
        //passed_cities =BellmanFord(adjacency_list,source,destination);
    
    }

    //there should be a loop to cout passed_cities

  }


  int main(){


    string s;
    cin>>s;


    Choose_Algo();
  }
  
