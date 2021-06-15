#pragma once
#include <unordered_map>
#include <map>
#include<windows.h>
#include <atlstr.h>
#include <random>

class Test {
  public:
    Test();
  public:
    int a;
    int b;
    virtual  void  test();
};

void testCpp() {
    std::vector<int> v1 = {1, 2};
    std::vector<int> v2 = {3, 4};

    std::copy(v1.begin(), v1.end(), v2.begin());

	std::uniform_int_distribution<int> dis(5,10);



}
