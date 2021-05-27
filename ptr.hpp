#pragma once
#include <memory>


class WeakFlag {

};

class SA {
  public:
    std::weak_ptr<WeakFlag> GetWeakFlag() {
        if (m_weakFlag.use_count() == 0) {
            m_weakFlag.reset((WeakFlag*)NULL);
        }

        return m_weakFlag;
    }
  private:
    std::shared_ptr<WeakFlag> m_weakFlag;
};


void testSharePtr(std::shared_ptr<int> sp1) {

    std::unique_ptr<int> up = std::make_unique<int>();


    std::weak_ptr<int> sp2 = sp1;
    //sp2.reset();
    int a = 0;
    std::shared_ptr<int> sp3 = sp2.lock();
    //int  use_count = sp3.use_count();
    //int test_count = sp2.use_count();

    //======================
    //std::shared_ptr<int> sp4 ;
    //std::shared_ptr<int> sp5 = sp4;
    //SA  sa;
    //auto p = sa.GetWeakFlag();

    //
    int sizesp2 = sizeof(sp1);
    int b = sizesp2;

    return;
}

void testPtr() {
    std::unique_ptr<double> p = std::make_unique<double>();
    int np = sizeof(p);

    std::weak_ptr<int> wp;
    std::shared_ptr<int> sp1 = std::make_shared<int>(1);
    testSharePtr(sp1);


    p.reset();

    if (p != nullptr) {
        int a = 10;
    }

    if (p.get() == nullptr) {
        int a = 10;
    }

    /* std::unique_ptr<int> p(new int);
    int x = 5;
    *p = 11;
    auto y = [p = std::move(p)]() {
    	std::cout << "inside: " << *p << "\n";
    };*/

    //y();
    //std::cout << "outside: " << *p << "\n";


    return;
}


int get_int() {
    int a = 5;
    return  a;
}

void testNew() {

    //int& a = 2; //# 左值引用绑定到右值，编译失败
    //int b = 2;        //# 非常量左值
    //const int& c = b; //# 常量左值引用绑定到非常量左值，编译通过
    //const int d = 2;  //# 常量左值
    //const int& e = c; //# 常量左值引用绑定到常量左值，编译通过
    //const int& b = 2;  //# 常量左值引用绑定到右值，编程通过

    //int a = 123;
    //auto&& b = 5;         //通用引用，可以接收右值
    //int&& c = a;          //错误，右值引用，不能接收左值
    //int&& c = get_int();   //正确
    //auto&& d = a;         //通用引用，可以接收左值
    //const auto&& e = a;   //错误，加了const就不再是通用引用了\


    return;
}

union MemNode {
    MemNode*    _next;
    char        _data[1];
};

void  testStruct() {
    int a = sizeof(MemNode);
    int b = a;
    return;
}



