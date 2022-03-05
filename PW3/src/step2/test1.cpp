#include <iostream>
#include <memory>
using namespace std;

class Test
{
public:
    Test(int in = 996) : id(in) { cout << "Test created." << endl; }
    void print() { cout << "this is class Test." << endl; }
    int getid() { return id; }
    ~Test() { cout << "Test deleted." << endl; }

private:
    int id;
};

int main()
{
    //weak_ptr<int> wpi(new int(996)); // 错误，weak_ptr不能直接通过普通指针引用对象
    shared_ptr<Test> spt(new Test(997));
    weak_ptr<Test> wpt = spt;
    spt->print();
    wpt.lock()->print();
    cout << wpt.lock()->getid() << endl; // 输出id(997)信息
    spt.reset();                         // spt被置为空指针，对象引用数变为0从而调用析构函数，析构时会输出信息
    cout << "spt deleted before here." << endl;
    wpt.lock()->print(); // print方法仍可以调用
    if (wpt.lock())      // 验证wpt.lock()的返回值
        wpt.lock()->print();
    else
        cout << "spt has been deleted, can not use wpt to access." << endl;
    cout << wpt.lock()->getid() << endl; // 错误，管理wpt的shared_ptr已释放，不能再通过weak_ptr访问id为997的对象
    return 0;
}