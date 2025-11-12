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

struct Item {
    int v, w;
    double r;
};

bool cmp(Item a, Item b) {
    return a.r > b.r;
}

// Fractional Knapsack (Greedy)
double fractionalKnapsack(int C, Item a[], int n) {
    for(int i=0; i<n; i++)
        a[i].r = (double)a[i].v / a[i].w;

    sort(a, a+n, cmp);

    double profit = 0;

    for(int i=0; i<n; i++) {
        if(C >= a[i].w) {
            profit += a[i].v;
            C -= a[i].w;
        } else {
            profit += a[i].v * ((double)C / a[i].w);
            break;
        }
    }
    return profit;
}

// 0/1 Greedy (NOT Always Optimal)
int greedy01(int C, Item a[], int n) {
    Item b[n];
    
    for(int i=0; i<n; i++) {
        b[i] = a[i];
        b[i].r = (double)b[i].v / b[i].w;
    }

    sort(b, b+n, cmp);

    int profit = 0;

    for(int i=0; i<n; i++) {
        if(C >= b[i].w) {
            profit += b[i].v;
            C -= b[i].w;
        }
    }
    return profit;
}

// 0/1 Knapsack (DP — Optimal)
int knapsackDP(int C, Item a[], int n) {
    int dp[n+1][C+1];

    for(int i=0; i<=n; i++)
        for(int w=0; w<=C; w++)
            dp[i][w] = 0;

    for(int i=1; i<=n; i++) {
        for(int w=1; w<=C; w++) {

            if(a[i-1].w <= w) {
                int include = a[i-1].v + dp[i-1][w - a[i-1].w];
                int exclude = dp[i-1][w];
                dp[i][w] = max(include, exclude);
            } 
            else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    return dp[n][C];
}

int main() {
    int n, C;

    cout << "Enter number of items: ";
    cin >> n;

    Item a[n];

    cout << "Enter value and weight of each item:\n";
    for(int i=0; i<n; i++) {
        cout << "Item " << i+1 << " (v w): ";
        cin >> a[i].v >> a[i].w;
    }

    cout << "Enter knapsack capacity: ";
    cin >> C;

    cout << "\nFractional Greedy: " << fractionalKnapsack(C, a, n) << endl;
    cout << "0/1 Greedy: " << greedy01(C, a, n) << endl;
    cout << "0/1 DP (Optimal): " << knapsackDP(C, a, n) << endl;
}

