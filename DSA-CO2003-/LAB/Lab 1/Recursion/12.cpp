#include<iostream>
using namespace std;

int strLen(char* str) {
    // Trường hợp cơ sở: nếu ký tự đầu tiên là '\0', độ dài là 0
    if (str[0] == '\0') {
        return 0;
    }
    // Trường hợp đệ quy: độ dài của chuỗi là 1 + độ dài của phần còn lại của chuỗi
    return 1 + strLen(str + 1);
}