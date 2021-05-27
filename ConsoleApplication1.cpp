// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdio.h>
#include<memory>
#include "classtest.hpp"
#include "sort.hpp"
#include "test.hpp"
#include "ptr.hpp"
#include "tree.hpp"
#include "math.hpp"
#include "string.hpp"
#include <assert.h>
#include "stl.hpp"

int main() {

    // Node* root = CreateTree(nullptr);
    // bfs_tree(root);
    //testPtr();
    //testNew();

    //testStruct();
    std::unique_ptr<int> ua = std::make_unique<int>();

    std::shared_ptr<int> pa = std::make_shared<int>();
    testSharePtr(pa);

    int a = 10;

    /*if (a == 10) {
        printf(" abort");
        assert(false);
    }*/

    int arr[] = {3, 5, 7, 9, 2, 8, 1};
    //int len = sizeof(arr) / sizeof(arr[0]);
    //BubbleSort(arr, len);
    testMath();

    //std::string testStr = genNewString("n2e3m");
    testStl();
    std::vector<int> v = {1, 2, 3, 4, 5};
    reverseArray(v);

    //



    getchar();
    return 0;
}


