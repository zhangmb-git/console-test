#pragma once
#include <vector>

void  QuickSort(int a[], int begin, int end) {
    return;
}

//
void  BubbleSort(int a[], int len) {

    int tmp = a[0];
    bool  change = true;

    for (int i = 0; i < len - 1; i++) {
        change = false;

        for (int j = 0; j < len - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                change = true;
            }
        }

        //if (!change) break;
    }

    std::vector<int> arrData;

    for (int i = 0; i < len; i++) {
        arrData.push_back(a[i]);
    }

    return;
}
