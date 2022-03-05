/* auto_ptr使用不当导致引用空指针 */

#include <iostream>
#include <memory>
using namespace std;

void print(auto_ptr<int> pi)
{
    cout << *pi << endl;
}

int main()
{
    auto_ptr<int> autopi(new int(806));
    print(autopi);
    if (!autopi.get())
        cout << "autopi has been null." << endl;
    *(autopi.get()) = 996; // 错误，autopi按值传递给print后已经被置为空指针
    cout << *autopi << endl;
    return 0;
}