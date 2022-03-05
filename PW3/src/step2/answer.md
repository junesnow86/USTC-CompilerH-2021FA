__step2__

1. weak_ptr 不可以直接通过普通指针引用对象，如下语句会在编译时报错：

    ```cpp
    weak_ptr<int> wpi(new int(996));
    ```

    错误信息：

    ```
    error: no matching function for call to ‘std::weak_ptr<int>::weak_ptr(int*)’
    
    /usr/include/c++/8/bits/shared_ptr.h:564:2: note: candidate: ‘template<class _Yp, class> std::weak_ptr<_Tp>::weak_ptr(std::weak_ptr<_Yp>&&)’
      weak_ptr(weak_ptr<_Yp>&& __r) noexcept
      ^~~~~~~~
      
    /usr/include/c++/8/bits/shared_ptr.h:564:2: note:   template argument deduction/substitution failed:
    test1.cpp:19:35: note:   mismatched types ‘std::weak_ptr<_Tp>’ and ‘int*’
    ```

    weak_ptr 只能由 shared_ptr 或 weak_ptr 通过直接构造或者拷贝构造来初始化。

2. weak_ptr 没有重载 `operator ->` 和 `operator *`，不可以直接通过 weak_ptr 使用它所指的对象，同时它也没有提供 `get` 方法直接获取裸指针，典型的用法是调用 `lock` 方法获取 shared_ptr 返回值来访问对象。所以如果管理 weak_ptr 的 shared_ptr 释放了，就不能通过 weak_ptr 访问对象了。

