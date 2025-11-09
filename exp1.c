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
    int value;
    int weight;
    double ratio;
};

// Compare function for sorting items by value/weight ratio (descending)
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

// ---------------------- FRACTIONAL KNAPSACK (GREEDY) ----------------------
double fractionalKnapsack(int capacity, Item items[], int n) {
    // Calculate value/weight ratio for each item
    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    // Sort items by ratio in descending order
    sort(items, items + n, compare);

    double totalValue = 0.0; // Total value in knapsack

    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            // Take the whole item
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            // Take a fraction of the item
            totalValue += items[i].value * ((double)capacity / items[i].weight);
            break; // Knapsack is full
        }
    }

    return totalValue;
}

// ---------------------- 0/1 KNAPSACK (DYNAMIC PROGRAMMING) ----------------------
int zeroOneKnapsack(int capacity, Item items[], int n) {
    int dp[n + 1][capacity + 1];

    // Build DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][capacity];
}

// ---------------------- MAIN FUNCTION ----------------------
int main() {
    int n;
    cout << "Enter number of items: ";
    cin >> n;

    Item* items = new Item[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter value of item " << i + 1 << ": ";
        cin >> items[i].value;
        cout << "Enter weight of item " << i + 1 << ": ";
        cin >> items[i].weight;
    }

    int capacity;
    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    // Compute results using both methods
    double fractionalResult = fractionalKnapsack(capacity, items, n);
    int zeroOneResult = zeroOneKnapsack(capacity, items, n);

    cout << "\n--------------------------------------------------\n";
    cout << "Results:\n";
    cout << "Maximum value in Fractional Knapsack (Greedy): " << fractionalResult << endl;
    cout << "Maximum value in 0/1 Knapsack (Dynamic Programming): " << zeroOneResult << endl;
    cout << "--------------------------------------------------\n";

    cout << "\nObservation:\n";
    cout << "→ Fractional Knapsack (Greedy) allows taking fractions of items, "
         << "so it can yield a higher total value.\n";
    cout << "→ 0/1 Knapsack (DP) only allows whole items but guarantees the optimal "
         << "solution for discrete cases.\n";
    cout << "→ Hence, the Greedy approach does not necessarily yield the optimal "
         << "solution compared to Dynamic Programming.\n";

    delete[] items;
    return 0;
}
