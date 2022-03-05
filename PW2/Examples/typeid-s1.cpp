#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
    int i = 5;
    float j = 1.0;
    char c = 'a';

    // get the type info
    const type_info &ti1 = typeid(i);
    const type_info &ti2 = typeid(j);
    const type_info &ti3 = typeid(c);
    const type_info &ti4 = typeid(i * j);
    const type_info &ti5 = typeid(i * c);

    // check if both types are same
    if (ti1 == ti2)
        cout << "i and j are of "
             << "similar type" << endl;
    else
        cout << "i and j are of "
             << "different type" << endl;

    if (ti1 == ti3)
        cout << "i and c are of "
             << "similar type" << endl;
    else
        cout << "i and c are of "
             << "different type" << endl;

    // print the types
    cout << "ti1 is of type " << ti1.name() << endl;
    cout << "ti2 is of type " << ti2.name() << endl;
    cout << "ti3 is of type " << ti3.name() << endl;
    cout << "ti4 is of type " << ti4.name() << endl;
    cout << "ti5 is of type " << ti5.name() << endl;
    return 0;
}
