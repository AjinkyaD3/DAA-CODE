#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> edges(E, vector<int>(3));

    cout << "Enter edges in format: source destination weight\n";
    for(int i = 0; i < E; i++) {
        cout << "Edge " << i+1 << ": ";
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Bellman-Ford Relaxation (Repeat V-1 times)
    for(int i = 1; i <= V-1; i++) {
        for(auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Negative Cycle Check
    for(auto &e : edges) {
        int u = e[0];
        int v = e[1];
        int w = e[2];

        if(dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "\nNegative cycle detected!\n";
            return 0;
        }
    }

    cout << "\nShortest distances from source " << src << ":\n";
    for(int i = 0; i < V; i++) {
        if(dist[i] == INT_MAX)
            cout << "Vertex " << i << ": INF\n";
        else
            cout << "Vertex " << i << ": " << dist[i] << "\n";
    }

    cout << "\nTime Complexity: O(V * E)\n";
}
