#include<iostream>
using namespace std;

void printHailstone(int number)
{        if (number==1) {cout<< "1"; return;}
    
     if( number%2==0)
          {  cout<< number<<" ";
            printHailstone(number/2);}
            
     else {
         cout<<number << " ";
        number*=3;
        number +=1;
        cout<< number<<" ";
        printHailstone(number/2);
     }
}