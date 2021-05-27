#pragma once
#include <string>
#include <string_view>
#include <iostream>
#include <cctype>

using namespace std;
string  genNewString(string src) {
    //src
    string new_str;
    int  sum = 0;

    for (int i = 0; i < src.size(); i++) {
        if (src[i] >= '0' && src[i] <= '9') {
            sum = sum * 10 + src[i] - '0';

        } else {
            if (sum != 0) {
                for (int j = 0; j < sum; j++) {
                    new_str.push_back('*');
                }

                sum = 0;
            }

            new_str.push_back(src[i]);
        }

        if (sum != 0) {
            for (int j = 0; j < sum; j++) {
                new_str.push_back('*');
            }

            sum = 0;
        }
    }

    return  new_str;
}

//
//string longestPalindrome(string s) {
//    for (int i = 0; i < s.length(); i++) {
//        for (int j = 2; j < s.length() - i - 1; j++) {
//            if (j % 2 == 0) { //Å¼Êý
//                string s1 = s.substr(i, j / 2);
//
//                string s2 = reverse(s.begin() + i + j / 2, j / 2);
//
//            } else { //ÆæÊý
//                string s1 = s.substr(i, j / 2);
//                string s2 = std::reverse(s.begin() + i + j / 2, j / 2);
//
//            }
//        }
//    }
//
//}
