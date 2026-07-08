#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <queue>
using namespace std;

int laven(const string& a,const string& b);
class city
{
    // node Neighbors; // (city — city ) → list
    public:
    /// 
    string name;
    static int cities_num;
    int id;
    float g;
    float h;
    float f;
    city * parent;
    /// 
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

class Bknode
{
    public :
        map<int,Bknode> children;
        city * node;
        int distance;
        Bknode()
        {
            node = NULL;
            distance = 0;
        }
        

};

class BK_Tree
{
    public:
    Bknode * root;

    BK_Tree()
    {
        root = NULL;
    }

    void insert(unordered_map<int,vector<pair<city,road>>> input,Bknode* word) 
    {
        if(root == NULL)
        {
            root = word; 
            return;
        }
        
        Bknode* current = root;

        while(true)
        {
           
            int dist= laven(word->node->name,current->node->name);
            
            if(dist == 0)
                return;
            
            if(current->children.count(dist)) // node exists
            {
                current = &(current->children.find(dist)->second); // go deeper
            }
            else
            {
                current->children[dist] = *word;
                return;
            }
        }
    }

    priority_queue<string> Search(const string& target,int tolernce = 5)
    {
        priority_queue<string> result;
        vector<Bknode*> q;
        q.push_back(root);  
        
        while(!q.empty())
        {
            Bknode* current = q.back();
            q.pop_back();

            int dist = laven(target,current->node->name);

            if (dist < tolernce)
            {
                result.push(current->node->name);
            }
            
            int low = dist - tolernce, high = dist + tolernce;

            for(auto& [distance,value] : current->children)
            {
                if(distance >= low && distance <= high)
                {
                    q.push_back(&value);
                }
            }
        }
        return result;
    }
    

};

int laven(const string& a, const string& b)
{
    
    int matrix[a.length() + 1][b.length() + 1]; 

    for(int j = 0 ; j <= b.length();++j)
    {
        matrix[0][j] = j;
    }
    
    for(int i = 0 ; i <= a.length();++i)
    {
        matrix[i][0] = i;
    }


    for(int i = 1 ; i <= a.length();++i) // row
    {
        for(int j = 1;j <= b.length(); ++j) // column
        {
            if (tolower(a[i-1]) != tolower(b[j-1])) 
            {
                matrix[i][j] = min({
                1 + matrix[i-1][j],  // deletion
                1 + matrix[i][j-1],  // insertion
                1 + matrix[i-1][j-1] // replacement
                                });
            }
            else
                matrix[i][j] = matrix[i-1][j-1];
        
        }
    }
    return matrix[a.length()][b.length()];
}
