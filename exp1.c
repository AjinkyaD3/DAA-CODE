/*
314448 (A) : Laboratory Practice-I (Design and Analysis of Algorithm)
Problem Statement:
Write a program to implement Fractional knapsack using Greedy algorithm and
0/1 knapsack using dynamic programming. Show that Greedy strategy does not
necessarily yield an optimal solution over a dynamic programming approach.
*/

#include <iostream>
#include <algorithm>
using namespace std;

struct Item{ int v,w; double r; };
bool cmp(Item a, Item b){ return a.r>b.r; }

// Fractional (Greedy)
double fractional(int c, Item a[], int n){
    for(int i=0;i<n;i++) a[i].r = (double)a[i].v/a[i].w;
    sort(a,a+n,cmp);
    double ans=0;
    for(int i=0;i<n;i++){
        if(c>=a[i].w){ ans+=a[i].v; c-=a[i].w; }
        else{ ans+=a[i].v*(double)c/a[i].w; break; }
    }
    return ans;
}

// 0/1 Greedy (not optimal)
int greedy01(int c, Item a[], int n){
    Item b[n];
    for(int i=0;i<n;i++) b[i]=a[i], b[i].r=(double)b[i].v/b[i].w;
    sort(b,b+n,cmp);
    int ans=0;
    for(int i=0;i<n;i++)
        if(c>=b[i].w) c-=b[i].w, ans+=b[i].v;
    return ans;
}

// 0/1 DP (optimal)
int dp01(int c, Item a[], int n){
    int dp[n+1][c+1]={0};
    for(int i=1;i<=n;i++)
        for(int w=1;w<=c;w++)
            dp[i][w]=(a[i-1].w<=w)?
                max(a[i-1].v+dp[i-1][w-a[i-1].w], dp[i-1][w]):
                dp[i-1][w];
    return dp[n][c];
}

int main(){
    int n,c; cin>>n;
    Item a[n];
    for(int i=0;i<n;i++) cin>>a[i].v>>a[i].w;
    cin>>c;

    cout<<"Fractional Greedy: "<<fractional(c,a,n)<<endl;
    cout<<"0/1 Greedy: "<<greedy01(c,a,n)<<endl;
    cout<<"0/1 DP (Optimal): "<<dp01(c,a,n)<<endl;
}
