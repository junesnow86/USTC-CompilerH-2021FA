__step2.2__

如果将 `Examples/typeid-s2.cpp` 中的 `printTypeinfo` 函数的第2个参数的类型中的 `B` 改成 `D`，程序将不能通过编译，输入编译命令，将得到以下报错：

```c
../Examples$ g++ typeid-s2.cpp
typeid-s2.cpp: In function ‘int main()’:
typeid-s2.cpp:28:25: error: invalid conversion from ‘B*’ to ‘const D*’ [-fpermissive]
     printTypeinfo("&b", &b);
                         ^~
typeid-s2.cpp:17:44: note:   initializing argument 2 of ‘void printTypeinfo(const char*, const D*)’
 void printTypeinfo(const char *n, const D *pb)
                                   ~~~~~~~~~^~
typeid-s2.cpp:30:26: error: invalid conversion from ‘B*’ to ‘const D*’ [-fpermissive]
     printTypeinfo("ptr", ptr);
                          ^~~
typeid-s2.cpp:17:44: note:   initializing argument 2 of ‘void printTypeinfo(const char*, const D*)’
 void printTypeinfo(const char *n, const D *pb)
                                   ~~~~~~~~~^~
```

原因是程序中的 `b` 是 `B` 类型的对象，虽然 `ptr` 实际指向的是 `D` 类型对象，但在定义时 `new` 返回的指针被隐式向上转换成了指向 `B` 类型的指针，传递参数时 `&b` 和 `ptr` 在编译阶段不能被向下转换成 `D` 类型指针，会导致编译阶段参数不匹配。

