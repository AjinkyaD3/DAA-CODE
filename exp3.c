/*
314448 (A): Laboratory Practice-I (Design and Analysis of Algorithm)
Problem Statement:
Write a recursive program to find the solution of placing n queens on the
chessboard so that no two queens attack each other using Backtracking.
*/
#include <iostream>
#include <vector>
using namespace std;

bool safe(int r, int c, vector<int>& b){
    for(int i=0;i<r;i++)
        if(b[i]==c || abs(b[i]-c)==abs(i-r)) return false;
    return true;
}

bool solve(int r, vector<int>& b, int n){
    if(r==n){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cout<<(b[i]==j?"Q ":"._ ");
            cout<<endl;
        }
        return true;
    }
    for(int c=0;c<n;c++){
        if(safe(r,c,b)){
            b[r]=c;
            if(solve(r+1,b,n)) return true;
        }
    }
    return false;
}

int main(){
    int n; cin>>n;
    vector<int> b(n,-1);
    if(!solve(0,b,n)) cout<<"No solution";
}
