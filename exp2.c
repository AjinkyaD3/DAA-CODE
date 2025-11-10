/*
314448 (A): Laboratory Practice-I (Design and Analysis of Algorithm)
Problem Statement:
Write a program to implement Bellman-Ford Algorithm using Dynamic Programming
and verify the time complexity.
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){
    int V,E; cin>>V>>E;
    vector<vector<int>> edges(E, vector<int>(3));
    for(int i=0;i<E;i++) cin>>edges[i][0]>>edges[i][1]>>edges[i][2];

    int src; cin>>src;
    vector<int> dist(V, INT_MAX);
    dist[src]=0;

    // Bellman-Ford (DP Relaxation)
    for(int i=1;i<V;i++)
        for(auto &e: edges)
            if(dist[e[0]]!=INT_MAX && dist[e[0]]+e[2]<dist[e[1]])
                dist[e[1]] = dist[e[0]] + e[2];

    // Check negative cycle
    for(auto &e: edges)
        if(dist[e[0]]!=INT_MAX && dist[e[0]]+e[2]<dist[e[1]]){
            cout<<"Negative cycle found";
            return 0;
        }

    // Output result
    for(int d: dist) 
        cout<<(d==INT_MAX?"INF":to_string(d))<<" ";
    cout<<"\nTime Complexity: O(V * E)\n";
}
