#include <iostream>
#include <typeinfo>
using namespace std;

class B
{
public:
    virtual void fun() { cout << "base fun" << endl; }
};

class D : public B
{
public:
    void fun() { cout << "derived fun" << endl; }
};

void printTypeinfo(const char *n, const B *pb)
{
    cout << "typeinfo(*" << n << ") is " << typeid(*pb).name() << endl;
}

int main()
{
    B b;
    D d;
    D *ptr = new D;
    B *p = new D;
    b.fun();
    d.fun();
    ptr->fun();
    p->fun();

    B *ptrb = dynamic_cast<B *>(ptr); // upcasting
    cout << "ptr is " << ptr << endl;
    cout << "ptrb is " << ptrb << endl;
    D *pd = dynamic_cast<D *>(p); // downcasting
    cout << "p is " << p << endl;
    cout << "pd is " << pd << endl;
    B *pb = dynamic_cast<B *>(p);
    cout << "pb is " << pb << endl;

    return 0;
}