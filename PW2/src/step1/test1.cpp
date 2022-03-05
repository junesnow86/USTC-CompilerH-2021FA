// 各种typeid情况
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <complex>
#include <utility>

/* 常用类型有哪些
 * int, short, long, unsigned int
 * float, double, long double
 * char, bool
 * enum
 * string, vectot<type>, 复数, pair
 * class
 * const
 * 引用
 * 指针
 */

enum state
{
    accepted,
    rejected
};

class Test
{
public:
    Test(int ID = 0) : _id(ID) {}
    int id() { return _id; }

private:
    int _id;
};

int main()
{
    // 定义各种各样的对象
    int item1;
    short item2;
    long item3;
    unsigned int item4;
    float item5;
    double item6;
    long double item7;
    char item8;
    bool item9;
    state item10;
    std::string item11;
    std::vector<Test> item12;
    std::complex<double> item13;
    std::pair<int, char> item14;
    Test item15;
    const int item16 = 806;
    int &item17 = item1;
    state *item18;
    const std::vector<Test> *item19;
    std::vector<int> item20(10);
    std::vector<int>::iterator iter = item20.begin();

    // 使用typeid查看它们的类型
    std::cout << "type of item1 is " << typeid(item1).name() << std::endl;
    std::cout << "type of item2 is " << typeid(item2).name() << std::endl;
    std::cout << "type of item3 is " << typeid(item3).name() << std::endl;
    std::cout << "type of item4 is " << typeid(item4).name() << std::endl;
    std::cout << "type of item5 is " << typeid(item5).name() << std::endl;
    std::cout << "type of item6 is " << typeid(item6).name() << std::endl;
    std::cout << "type of item7 is " << typeid(item7).name() << std::endl;
    std::cout << "type of item8 is " << typeid(item8).name() << std::endl;
    std::cout << "type of item9 is " << typeid(item9).name() << std::endl;
    std::cout << "type of item10 is " << typeid(item10).name() << std::endl;
    std::cout << "type of item11 is " << typeid(item11).name() << std::endl;
    std::cout << "type of item12 is " << typeid(item12).name() << std::endl;
    std::cout << "type of item13 is " << typeid(item13).name() << std::endl;
    std::cout << "type of item14 is " << typeid(item14).name() << std::endl;
    std::cout << "type of item15 is " << typeid(item15).name() << std::endl;
    std::cout << "type of item16 is " << typeid(item16).name() << std::endl;
    std::cout << "type of item17 is " << typeid(item17).name() << std::endl;
    std::cout << "type of item18 is " << typeid(item18).name() << std::endl;
    std::cout << "type of item19 is " << typeid(item19).name() << std::endl;
    std::cout << "type of expression(item20) is " << typeid(iter + 3).name() << std::endl;

    return 0;
}