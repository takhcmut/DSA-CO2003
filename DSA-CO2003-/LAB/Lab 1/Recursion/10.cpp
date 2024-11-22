#include<iostream>
using namespace std;

int mininumBracketAddSupport(const string &str, size_t opencount, size_t closecount, size_t index){
    if (index == str.size()){
        return opencount + closecount;
    }

    char currentChar = str[index];

    if (currentChar == '('){
        return mininumBracketAddSupport(str, opencount + 1, closecount, index + 1);
    }
    else {
        if (opencount >= 1){
            return mininumBracketAddSupport(str, opencount - 1, closecount, index + 1);
        }
        else {
            return mininumBracketAddSupport(str, opencount, closecount + 1, index + 1);
        }
    }
}

int mininumBracketAdd(const string& str){
   return mininumBracketAddSupport(str, 0, 0, 0);
}