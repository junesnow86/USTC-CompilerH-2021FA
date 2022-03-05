#include <iostream>
#include <memory>
using namespace std;

int main()
{
    auto x = new int(996);
    unique_ptr<int> uptr(x);
    shared_ptr<int> sptr1(x);
    weak_ptr<int> wptr(x);
    if (x == nullptr)
        cout << "true" << endl;
    else
        cout << "x = " << x << " " << *x << endl;
    //unique_ptr<int> uptr = sptr1;
    cout << "uptr = " << uptr.get() << endl;
    cout << "sptr1 = " << sptr1.get() << endl;
    cout << sptr1.use_count();
    {
        weak_ptr<int> sptr2 = sptr1;
        auto sptr3 = sptr1;
        cout << sptr1.use_count();
    }
    cout << sptr1.use_count();
    cout << "x = " << x << " " << *x << endl;
    return 0;
}