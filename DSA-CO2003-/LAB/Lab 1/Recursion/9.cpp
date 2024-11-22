#include<iostream>
using namespace std;

int findGCD(int a, int b) {
    if (b == 0)
        return a;
    return findGCD(b, a % b);
}

// Hàm tìm LCM sử dụng đệ quy
int findLCMUtil(int a, int b, int multiple) {
    if (multiple % a == 0 && multiple % b == 0)
        return multiple;
    return findLCMUtil(a, b, multiple + max(a, b));
}

int findLCM(int a, int b) {
    return findLCMUtil(a, b, max(a, b));
}
