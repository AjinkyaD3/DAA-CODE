/*
314448 (A): Laboratory Practice-I (Design and Analysis of Algorithm)
Problem Statement:
Write a program to implement Fractional knapsack using Greedy algorithm and 0/1
knapsack using dynamic programming. Show that Greedy strategy does not
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

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(int capacity, Item items[], int n) {
    for (int i = 0; i < n; i++) {
        items[i].ratio = static_cast<double>(items[i].value) / items[i].weight;
    }

    sort(items, items + n, compare);

    double totalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].value *
                          (static_cast<double>(capacity) / items[i].weight);
            break;
        }
    }

    return totalValue;
}

int main() {
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    Item* items = new Item[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter value of item " << i + 1 << ": ";
        cin >> items[i].value;
        cout << "Enter weight of item " << i + 1 << ": ";
        cin >> items[i].weight;
    }

    int capacity;
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    double maxValue = fractionalKnapsack(capacity, items, n);
    cout << "Maximum value in Fractional Knapsack = " << maxValue << endl;

    delete[] items;
    return 0;
}
