/*
314448 (A): Laboratory Practice-I (Design and Analysis of Algorithm)
Problem Statement:
Write a program to solve the travelling salesman problem and to print the path
and the cost using LC Branch and Bound.
*/
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

struct Node{
    vector<int> path;
    vector<bool> vis;
    int cost, lb, lvl;
    bool operator>(const Node& o) const { return lb > o.lb; }
};

int boundCalc(const Node& nd, vector<vector<int>>& d, int n){
    int b = nd.cost, last = nd.path.back();
    for(int i=0;i<n;i++){
        if(!nd.vis[i]){
            int mn = INT_MAX;
            for(int j=0;j<n;j++) if(i!=j) mn = min(mn, d[j][i]);
            b += mn;
        }
    }
    return b;
}

int main(){
    int n; cin>>n;
    vector<vector<int>> d(n, vector<int>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>d[i][j];

    priority_queue<Node,vector<Node>,greater<Node>> pq;
    Node st; 
    st.path={0}; st.vis=vector<bool>(n,false); st.vis[0]=true;
    st.cost=0; st.lvl=1; st.lb = boundCalc(st,d,n);
    pq.push(st);

    int best = INT_MAX; vector<int> bestPath;

    while(!pq.empty()){
        Node cur = pq.top(); pq.pop();
        if(cur.lb >= best) continue;
        if(cur.lvl == n){
            int total = cur.cost + d[cur.path.back()][0];
            if(total < best){ best = total; bestPath = cur.path; bestPath.push_back(0); }
            continue;
        }
        for(int i=0;i<n;i++){
            if(!cur.vis[i]){
                Node nxt = cur;
                nxt.path.push_back(i);
                nxt.vis[i]=true;
                nxt.cost += d[cur.path.back()][i];
                nxt.lvl++;
                nxt.lb = boundCalc(nxt,d,n);
                if(nxt.lb < best) pq.push(nxt);
            }
        }
    }

    cout<<"Minimum Cost: "<<best<<"\nPath: ";
    for(int i: bestPath) cout<<i<<" ";
}
