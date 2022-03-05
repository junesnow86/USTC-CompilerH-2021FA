__step1__

unique_ptr 不可以通过按值传递给函数，但可以通过引用传递。因为按值传递实际上就是直接将实参赋值(=)给函数局部变量，但是 unique_ptr 不允许直接赋值；但是通过引用传递给函数就没有发生赋值，在函数中直接使用原来的 unique_ptr 是可以的。通过以下一个简单的小程序可以验证：

```cpp
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
```

编译时会输出以下错误信息：

```
../src/step1$ g++ verify.cpp -o verify
verify.cpp: In function ‘int main()’:
verify.cpp:19:14: error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
     printv(pi);
              ^
In file included from /usr/include/c++/8/memory:80,
                 from verify.cpp:2:
/usr/include/c++/8/bits/unique_ptr.h:394:7: note: declared here
       unique_ptr(const unique_ptr&) = delete;
       ^~~~~~~~~~
verify.cpp:10:6: note:   initializing argument 1 of ‘void printv(std::unique_ptr<int>)’
 void printv(unique_ptr<int> pi)
      ^~~~~~
```

注释掉 `printv` 函数时可以编译通过并运行。