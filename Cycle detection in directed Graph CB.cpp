#include<iostream>
#include<queue>
#include<map>
#include<list>
using namespace std;

template<typename T>
class graph{

    map<T,list<T>> adjMap;
public:
    void addEdge(T u,T v,bool bidir=true){
    adjMap[u].push_back(v);
    if(bidir){
        adjMap[v].push_back(u);
    }
    }

    void print()
    {
    for(auto i:adjMap){
        cout<<i.first<<"->";
        for(auto spunk:i.second){
            cout<<spunk<<",";
        }
        cout<<endl;
    }
    }

void bfs(T src){
      queue<T> q;
      map<T,int> dist;
      map<T,T> parent;
        for(auto i:adjMap){
            dist[i.first]=INT_MAX;
        }
        q.push(src);
        dist[src]=0;
        parent[src]=src;
        while(!q.empty()){
            T node = q.front();

            q.pop();
            for(int neighbour:adjMap[node]){
                if(dist[neighbour]==INT_MAX){
                    q.push(neighbour);
                    dist[neighbour]=dist[node]+1;
                    parent[neighbour]=node;
                }
            }
        }
        //print
        for(auto i:adjMap){
            T node=i.first;
            cout<<"Distance of "<<node<<" from "<<src<<" is "<<dist[node]<<endl;
        }
}

    /*void dfsHelper(T node,map<T,bool> &visited){

        visited[node]=true;
        cout<<node<<" ";
        for(T neighbour:adjMap[node]){
            if(!visited[neighbour]){
                dfsHelper(neighbour,visited);
            }
        }
    }*/

    void dfs(T src){

        map<T,bool> visited;
        int component=1;
        dfsHelper(src,visited);
        cout<<endl;
        for(auto i:adjMap){
            T city=i.first;
            if(!visited[city]){
                dfsHelper(city,visited);
                component++;
            }
        }
        cout<<"The current graph has "<<component<<" components.";
    }

    void dfsHelper(T node,map<T,bool> &visited, list<T> &ordering){
        visited[node]=true;

        for (T neighbour:adjMap[node]){
            if(!visited[neighbour]){
                dfsHelper(neighbour,visited,ordering);
            }
        }
        ordering.push_front(node);
    }

    void topological(){

        queue<T> q;
        map<T,bool> visited;
        map<T,int> indegree;
        for(auto i: adjMap){
            T node = i.first;
            visited[node]=false;
            indegree[node]=0;
        }
        for(auto i:adjMap){
            T u=i.first;
            for(T v:adjMap[u]){
                indegree[v]++;
            }
        }
        for(auto i:adjMap){
            T node=i.first;
            if(indegree[node]==0){
                q.push(node);
            }
        }
        while(!q.empty()){
            T node=q.front();
            q.pop();
            cout<<node<<"-->";
            for(T neighbour:adjMap[node]){
                indegree[neighbour]--;
                if(indegree[neighbour]==0){
                    q.push(neighbour);
                }
            }
        }
    }

    bool isCyclicHelper(T node,map<T,bool> &visited,map<T,bool> &inStack){

        visited[node]=true;
        inStack[node]=true;

        for(T neighbour:adjMap[node]){
             //a node is not visited but its branch is leading to a cycle, then it will return true , that it is a cycle
            if(!visited[neighbour] && isCyclicHelper(neighbour,visited,inStack) || inStack[neighbour]){

                return true;
            }
        }
            inStack[node]=false;
            return false;
    }

    bool isCyclic(){

    map<T,bool> visited;
    map<T,bool> inStack;
    for(auto i:adjMap){
        T node=i.first;
        if(!visited[node]){
            bool cyclepresent=isCyclicHelper(node,visited,inStack);
            if(cyclepresent){
                return true;
            }
        }
    }
    return false;
    }

};

int main ()
{
    //graph<int> g;

    graph<int> g;

    g.addEdge(0,2,false);
    g.addEdge(0,1,false);
    g.addEdge(2,3,false);
    g.addEdge(2,4,false);
   // g.addEdge(3,0,false);
    g.addEdge(4,5,false);
    g.addEdge(1,5,false);
    //g.addEdge(,,false);

    if(g.isCyclic()){
            cout<<"Graph is cyclic";
    }
    else{
        cout<<"Not cyclic";
    }
    return 0;
}
