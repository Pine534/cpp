#include<iostream>
using namespace std;

class A
{
public:
    virtual void func1() {
        cout << "A func1" << endl;
    }
    virtual void func2() {
        cout << "A func2" << endl;
    }
};

class B : virtual public A
{
public:
    virtual void func1() {
        cout << "B func1" << endl;
    }
};

class C : virtual public A
{
public:
    virtual void func2() {
        cout << "C func2" << endl;
    }
};

class D : public B, public C
{
public:
    // void func1() {
    //     cout << "D func1" << endl;
    // }
    virtual void func2() {
        cout << "D func2" << endl;
    }
};
int main()
{
    A* ptrA = new D();
    ptrA->func1();
    ptrA->func2();
}