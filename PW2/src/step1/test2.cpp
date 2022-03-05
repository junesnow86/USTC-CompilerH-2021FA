/* 常见类型转换 */
/* static_cast
 * 良性转换
 * void 指针和具体类型指针
 * 有转换构造函数或者类型转换函数的类与其他类型之间的转换
 */
/* dynamic_cast
 * 指针和引用
 * 向上转换
 * 向下转换
 */

#include <iostream>
#include <string>
#include <complex>

class Base
{
public:
    virtual ~Base() {}
};

class Derived : public Base
{
public:
    void print() { std::cout << "this is Derived." << std::endl; }
};

enum mumble
{
    m1,
    m2,
    m3
};

int main()
{
    /* static_cast */
    mumble mval = m2;
    char cval = static_cast<char>(mval);
    std::cout << "char(mval): " << cval << std::endl;
    int ival = static_cast<int>(mval);
    std::cout << "int(mval): " << ival << std::endl;

    const void *pcv = 0;
    void *pv = 0;
    pv = &ival;                                       // OK
    pcv = &ival;                                      // OK，可以把非const数据类型的地址赋值给const指针
    int *pi = static_cast<int *>(pv);                 // OK，把实际指向int型数据的void指针赋值给int指针
    std::string *ps = static_cast<std::string *>(pv); // 不安全，pv实际指向的是int型对象
    const int cival = ival;
    pv = static_cast<void *>(&cival); // 错误，不能把const数据类型的地址赋值给非const指针，强制转换无效

    std::complex<double> cp(80.6, 9.19);
    double img = static_cast<double>(cp); // 错误，不存在从标准库复数类到double型的适当的转换函数

    /* dynamic_cast */
    Derived *pd = new Derived;
    Base *pb = dynamic_cast<Base *>(pd); // 向上转换，与Base* pb = pd;等价

    Base *pb2 = new Derived;
    Derived *pd2 = dynamic_cast<Derived *>(pb2); // 只有当pb2实际指向的是Derived对象时才是安全的
    Base &ob2 = (*pb2);                          // OK，*pb2向上转换成Base类型后再取引用
    Derived &od2 = dynamic_cast<Derived &>(ob2); // OK，引用的安全向下转换

    Base *pb3 = new Base;
    Derived *pd3 = dynamic_cast<Derived *>(pb3); // 不安全的向下转换，会返回nullptr
    if (pd3 == nullptr)
        std::cout << "nullptr" << std::endl;
    Base &ob3 = (*pb3);
    Derived &od3 = dynamic_cast<Derived &>(ob3); // 不安全的向下转换，会抛出bad_cast

    return 0;
}