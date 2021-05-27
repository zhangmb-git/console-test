#pragma once
#include <vector>
#include <iostream>
#include <iterator>
#include <vector>

void  testStl() {
    std::vector<int> v{ 3, 1, 4};

    auto it = v.end();
    auto pv = std::prev(it, 2);
    std::cout << *pv << '\n';

    it = v.begin();
    pv = std::prev(it, -2);
    std::cout << *pv << '\n';
    return;
}

void reverseArray(std::vector<int>& v) {
    int  tmp = 0;

    // for (int i = 0, j = v.size() - 1; i < j; i++, j--) {
    //     std::swap(v[i], v[j]);
    // }
    std::reverse(v.begin(), v.end());
    int a = 10;
    return;
}


