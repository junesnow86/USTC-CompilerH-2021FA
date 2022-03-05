#include <iostream>
#include <memory>
using namespace std;

void printq(unique_ptr<int> &pi)
{
    cout << *pi << endl;
}

void printv(unique_ptr<int> pi)
{
    cout << *pi << endl;
}

int main()
{
    unique_ptr<int> pi(new int(996));
    printq(pi);
    printv(pi);
    return 0;
}