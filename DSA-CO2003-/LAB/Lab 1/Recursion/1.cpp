#include<iostream>
using namespace std;

void printArray(int n)
{       static int i =0;
        if(i==n) {
            cout<<i;
            return;}
        
        
        cout<<i<<", ";
         i++;
        printArray(n);
       
}