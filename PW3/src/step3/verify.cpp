#include <iostream>
#include <memory>
using namespace std;

class A
{
public:
    ~A() { cout << "H" << endl; }
};

int main()
{
    {
        unique_ptr<A> upa(new A());
        unique_ptr<A> upa2 = move(upa);
        upa2.release();
        cout << "is here a 'H'?" << endl;
    }
    cout << "here is a 'H'." << endl;
    return 0;
}