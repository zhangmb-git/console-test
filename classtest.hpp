#pragma once
#include <memory>
#include <iostream>

class A {
  public:
    A(int a) {
        printf("%d=== \n", 0);
    };

    A(A& a) {
        printf("%d=== \n", 1);
    }
    A(const A& a) {
        printf("%d=== \n", 2);
    }

    A& operator=(A& a) {
        printf("%d=== \n", 3);
        return *this;
    }

    A& operator=(const A& a) {
        printf("%d=== \n", 4);
        return *this;
    }

  private:
    int a;

};


struct tagA {
    int64_t  c;
    char b;
    int a;
};

void testClass() {
    A* pc = new A(2);
    A* pd = pc;
    int* pa = new int;
    *pa = 1;
    return;
}


