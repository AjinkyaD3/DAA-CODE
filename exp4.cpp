#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

struct Node {
    vector<int> path;
    vector<bool> vis;
    int cost, lb, lvl;

    bool operator>(const Node& o) const {
        return lb > o.lb; // For min-priority queue (lower bound first)
    }
};

// Calculate Lower Bound
int boundCalc(const Node& nd, vector<vector<int>>& d, int n) {
    int b = nd.cost;
    for(int i = 0; i < n; i++) {
        if(!nd.vis[i]) {
            int mn = INT_MAX;
            for(int j = 0; j < n; j++) {
                if(i != j) mn = min(mn, d[j][i]);
            }
            b += mn;
        }
    }
    return b;
}

int main() {
    int n;

    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> d(n, vector<int>(n));

    cout << "\nEnter cost matrix (Distance between cities):\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    Node start;
    start.path = {0};                 // Start at city 0
    start.vis = vector<bool>(n, false);
    start.vis[0] = true;
    start.cost = 0;
    start.lvl = 1;
    start.lb = boundCalc(start, d, n);
    pq.push(start);

    int best = INT_MAX;
    vector<int> bestPath;

    while(!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if(cur.lb >= best)
            continue;

        if(cur.lvl == n) {
            int tourCost = cur.cost + d[cur.path.back()][0];
            if(tourCost < best) {
                best = tourCost;
                bestPath = cur.path;
                bestPath.push_back(0); 
            }
            continue;
        }

        for(int i = 0; i < n; i++) {
            if(!cur.vis[i]) {
                Node nxt = cur;
                nxt.path.push_back(i);
                nxt.vis[i] = true;
                nxt.cost += d[cur.path.back()][i];
                nxt.lvl++;
                nxt.lb = boundCalc(nxt, d, n);

                if(nxt.lb < best)
                    pq.push(nxt);
            }
        }
    }

    cout << "\nMinimum Cost: " << best << endl;
    cout << "Path: ";
    for(int city : bestPath) cout << city << " ";

    cout << endl;
    return 0;
}
