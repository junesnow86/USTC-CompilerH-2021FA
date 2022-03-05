## 第一关

`%2 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 %0`

参数解释：该指令返回一个`i32*`类型的值(一个地址值)给%2，第一个参数是计算基础类型，第二个参数表示指针类型(数组的元素类型和元素个数)，第三个参数为指针，再往后的`i32 0`表示起始索引号，`i32 %0`为偏移量。

## 第三关

`Scope::name2var`：一个作用域对应vector中的一个元素，当前作用域就是最后一个元素，vector中的一个元素是一个(变量)符号表；全局域是vector中的第一个元素。

加法表达式所有情况：

* 算数表达式
    * float加法
    * int加法
    * 地址加

### Question

1. 需要考虑指针加法吗？

    ```c
    int a[3] = {0, 1, 2};  // 这里a应该是array_type才对...
    if (a+1) {
        ...
    }
    ```

    不需要！
    
2. 320行