#include<iostream>
#include<string>
using namespace std;

// Hàm trợ giúp để tìm từ tiếp theo trong câu sử dụng đệ quy
string getNextWord(const string &s, size_t &index) {
    if (index >= s.length() || s[index] == ' ') {
        return "";
    }
    string word(1, s[index]);
    index++;
    return word + getNextWord(s, index);
}

// Hàm trợ giúp để bỏ qua khoảng trắng
void skipSpace(const string &s, size_t &index) {
    if (index < s.length() && s[index] == ' ') {
        index++;
    }
}

// Hàm đệ quy để đảo ngược câu
string reverseSentenceHelper(const string &s, size_t &index) {
    if (index >= s.length()) {
        return "";
    }
    string word = getNextWord(s, index);
    skipSpace(s, index);
    string remainingSentence = reverseSentenceHelper(s, index);
    if (remainingSentence.empty()) {
        return word;
    }
    return remainingSentence + " " + word;
}

string reverseSentence(string s) {
    size_t index = 0;
    return reverseSentenceHelper(s, index);
}