#include<iostream>
using namespace std;

void printPatternSP(int n, int index, bool isdegree){
    cout << n;
    if (n == index && !isdegree){
        return;
    }

    cout << " ";

    if (isdegree){
        if (n - 5 > 0){
            return printPatternSP(n - 5, index, true);
        }
        else{
            return printPatternSP(n - 5, index, false);
        }
    }
    else{
        return printPatternSP(n + 5, index, false);
    }
    }


void printPattern(int n){
    printPatternSP(n, n, true);
}