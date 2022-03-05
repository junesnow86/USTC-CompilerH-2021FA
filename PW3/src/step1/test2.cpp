/* auto_ptr使用不当导致内存泄露 */

#include <iostream>
#include <memory>
using namespace std;

class Test
{
public:
    Test() { cout << "Test created." << endl; }
    ~Test() { cout << "Test deleted" << endl; }
};

void func(auto_ptr<Test> pt)
{
    return;
}

int main()
{
    /* 正确地释放数组时会输出三条"Test deleted"信息
    Test *test = new Test[3];
    delete[] test;
    */

    auto_ptr<Test> pt(new Test[3]);
    func(pt); // pi按值传递给func时会释放pi所指内存，但是使用的是非数组的delete，会导致内存泄露
    // 实际输出只有1条"Test deleted"信息，说明实际上只释放了test数组的第一个元素的内存空间
    if (pt.get() == nullptr)
        cout << "pi is NULL now" << endl; // 验证pt确实是被置为空指针了
    return 0;
}