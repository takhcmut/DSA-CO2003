#include<iostream>
#include<string>
using namespace std;

string repeatString(const string &str, int count) {
    if (count <= 0) {
        return "";
    }
    return str + repeatString(str, count - 1);
}
string expandHelper(const string &s, size_t &index) {
    string result;
    if (index >= s.length()) {
        return result;
    }
    
    if (isdigit(s[index])) {
        int repeat = s[index] - '0';
        index++; // move past the digit
        if (s[index] == '(') {
            index++; // move past the '('
            string subResult = expandHelper(s, index);
            result += repeatString(subResult, repeat);
        }
    } else if (s[index] == ')') {
        index++; // move past the ')'
        return result;
    } else {
        result += s[index];
        index++;
    }

    return result + expandHelper(s, index);
}

string expand(string s) {
    size_t index = 0;
    return expandHelper(s, index);
}