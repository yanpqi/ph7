#include <iostream>
using namespace std;
int g_ctor=0;
int g_copy=0;
int g_dtor=0;

// compiled with this:
// g++ -std=c++11 -o right_ref right_ref.cc -fno-elide-constructors
// See https://www.cnblogs.com/qicosmos/p/4283455.htm
l
class A {
public:
    A() {
        cout << "ctor " << ++g_ctor << endl;
    }
    A(const A& a) {
        cout << "copy " << ++g_copy << endl;
    }
    ~A() {
        cout << "dtor " << ++g_dtor << endl;
    }
};

A getA() {
    return A();
}

int main() {
    // A a = getA();
    // A&& a = getA();
    // A& a = getA();
    const A& a = getA();
    return 0;
}
