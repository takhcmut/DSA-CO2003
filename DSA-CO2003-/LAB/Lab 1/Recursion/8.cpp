#include<iostream>
#include<cmath>
using namespace std;

int myArrayToIntUtil(char* str, int n) {
    // Trường hợp cơ sở: nếu chỉ còn 1 ký tự, trả về giá trị số của ký tự đó
    if (n == 1)
        return str[0] - '0';

    // Đệ quy: chuyển đổi ký tự đầu tiên thành số và cộng với kết quả của phần còn lại
    return (str[0] - '0') * pow(10, n - 1) + myArrayToIntUtil(str + 1, n - 1);
}

int myArrayToInt(char* str, int n) {
    return myArrayToIntUtil(str, n);
}