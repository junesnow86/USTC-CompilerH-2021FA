#include <iostream>
#include <typeinfo>

class Base
{
public:
    virtual ~Base() {}
};

class Derived : public Base
{
};

Derived derived;
Base *ptr = &derived;

int main()
{
    std::cout << "typeid(ptr) = " << typeid(ptr).name() << std::endl;
    std::cout << "typeid(*ptr) = " << typeid(*ptr).name() << std::endl;
    return 0;
}