**问题2-1**

1. `-nostdinc` 使编译器不在系统默认的头文件目录里搜索头文件

2. 通过使用命令 `gcc -xc -E -v -` 得到 `gcc` C程序默认的头文件查找路径按顺序如下：

    ```
    #include "..." search starts here:
    #include <...> search starts here:
     /usr/lib/gcc/x86_64-linux-gnu/5/include
     /usr/local/include
     /usr/lib/gcc/x86_64-linux-gnu/5/include-fixed
     /usr/include/x86_64-linux-gnu
     /usr/include
    End of search list.
    ```

3. 可以添加 `-I` 选项，要求 `gcc` 到指定的 多个`dir` 目录中查找头文件，输入命令 `gcc -nostdinc -I dir1 -I dir2 ... sample.c -o sample`，将上述默认路径全部显式指定，就可以使程序通过编译

**问题2-2**

1. `-nostdlib` 使编译器不连接系统标准启动文件和标准库文件。

2. 先编译链接得到 `sample-io`，再使用 `ldd sample-io` 得到以下库文件：

    ```
    linux-vdso.so.1
    /lib/x86_64-linux-gnu/libc.so.6
    /lib64/ld-linux-x86-64.so.2
    ```

3. 使用如下命令：

    ```
    gcc -nostdlib -o sample-io /lib64/ld-linux-x86-64.so.2 /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o /usr/lib/x86_64-linux-gnu/crtn.o -lc sample-io.c
    ```

    可以使程序通过编译，生成可以正常运行的 `sample-io` 可执行文件，运行后得到：

    ```
    root@evassh-6197455:/data/workspace/myshixun# ./sample-io
    Hello, world!
    a=8
    ```

    `gcc` 将以下路径传递给在链接阶段调用的链接器 `ld` ：

    * `/lib64/ld-linux-x86-64.so.2`：这是 `ld` 需要的动态链接器位置

    * ```
        /usr/lib/x86_64-linux-gnu/crt1.o 
        /usr/lib/x86_64-linux-gnu/crti.o 
        /usr/lib/x86_64-linux-gnu/crtn.o
        ```

        这三个是需要的 `CRT(C Run-Time)` 库文件，这些库文件包含程序的入口函数 `_start` 等不可缺少的函数。 

    * `-lc` ：通过 `-l` 参数指定链接C标准库，其中提供负责调用 `CRT` 库函数的函数。

    以上路径传递给 `ld` 后就可以正常链接然后生成可执行文件了。

