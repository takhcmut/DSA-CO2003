// Hàm đệ quy để loại bỏ khoảng trắng và chuyển thành chữ thường
#include<string>
#include<iostream>
using namespace std;

string preprocessString(const string& str, unsigned int index = 0) {
    if (index == str.size()) {      // neu chay den phan tu o ngoai thi bang rong
        return "";
    }
    char c = str[index];
    if (!isspace(c)) {
        // return string(1, tolower(c)) + preprocessString(str, index + 1);
                //string strtmp(1,tolower(c));
                string strtmp ="";
                strtmp+= tolower(c);
                 strtmp += preprocessString(str, index + 1);
        return strtmp;                                                                               
    }
    return preprocessString(str, index + 1);
}

// Hàm đệ quy kiểm tra palindrome
bool isPalindromeHelper(const string& str, unsigned int left, unsigned int right) {
    // Trường hợp cơ bản
    if (left >= right) {
        return true;
    }
    // Kiểm tra ký tự đầu và cuối
    if (str[left] != str[right]) {
        return false;
    }
    // Gọi đệ quy kiểm tra phần còn lại của chuỗi
    return isPalindromeHelper(str, left + 1, right - 1);
}

// Hàm chính để kiểm tra palindrome
bool isPalindrome(string str) {
    string processedStr = preprocessString(str);
    return isPalindromeHelper(processedStr, 0, processedStr.length() - 1);
}