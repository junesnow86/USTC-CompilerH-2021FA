[TOC]

---

### 任务描述
**本关任务**：熟悉LLVM IR，并根据给出的4个SysYF程序(文件扩展名为sy)手写相应的LLVM IR的ll文件，以实现相同功能。

### 相关知识
#### LLVM IR介绍
[LLVM](https://llvm.org/)是一个开源的编译器基础设施，用C++语言编写，包含一系列模块化的编译器组件和工具链，用来支持编译器前端和后端的开发。IR的全称是Intermediate Representation，即中间表示。LLVM IR是一种类型化的三地址中间表示，是类似于汇编的底层语言。  
LLVM IR的具体指令可以参考[Reference Manual](http://llvm.org/docs/LangRef.html)。但是你会发现其内容庞杂，为便于你尽快了解本实训项目需要涉及的LLVM IR指令子集，请查看本实训提供的**精简的IR Reference手册**`doc/SysYFIR.md`。  
作为一开始的参考，你可以先阅读其中的`IR Features`和`IR Format`两节，后续有需要再反复参考。

#### 样例学习
<details>
  <summary> go_upstairs.c（点击展开） </summary>

```c
int num[2] = {4, 8};
int x[1];
int n;
int tmp = 1;

int climbStairs(int n) {
    if(n < 4)
        return n;
    int dp[10];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    int i;
    i = 3;
    while(i<n+1){
        dp[i] = dp[i-1] + dp[i-2];
        i = i + 1;
    }
    return dp[n];
}

int main(){
    int res;
    n=num[0];
    x[0] = num[tmp];
    res = climbStairs(n + tmp);
    return res - x[0];
}
```
</details>


- 阅读`Student/task1/demo/go_upstairs.c`。  
- 进入`Student/task1/demo`文件夹，输入命令

	```clang -S -emit-llvm go_upstairs.c```
你可以得到对应的`go_upstairs.ll`。  
你需要结合`go_upstairs.c`阅读`go_upstairs.ll`，理解其中每条LLVM IR指令与C代码的对应情况。  
- 通过执行命令
	```lli go_upstairs.ll; echo $?```
你可以测试`go_upstairs.ll`执行结果的正确性。  

### 本关具体任务
1. 在`Student/task1/student_sy/`内提供了四个简单的SysYF 程序：`assign_test.sy`，`func_test.sy`，`if_test.sy`，`while_test.sy`。  
你需要在`Student/task1/ll/`目录下手工编写`assign_hand.ll`，`func_hand.ll`，`if_hand.ll`，`while_hand.ll`文件，以实现与上述 SysYF 程序相同的逻辑功能。  
你需要在`ll`文件内添加必要的注释，`ll`文件的注释是以`;`开头的。  
必要的情况下，你可以参考`clang -S -emit-llvm`的输出，但是你提交的结果必须避免同此输出一字不差。  
2. 在`report.md`内回答[思考题](#思考题)

### 运行说明
- 你需要使用 `clang --version` 和 `lli --version` 检查本机的Clang和LLVM版本
- 你可以使用 `which lli` 来查找 `lli` 命令的位置
- 利用LLVM的命令 `lli`，可以执行`*.ll`文件；如果版本过低，可能会遇到`error: expected top-level entity`等问题
- 你也可以使用 `clang go_upstairs.ll -o go_upstairs` 来生成可执行文件
- `$?`的内容是上一条命令所返回的结果，而`echo $?`可以将其输出到终端中
- 使用`clang`时，注意扩展名为`sy`的文件是SysYF语言的程序文件，`clang`是无法直接识别的，你可以将`sy`文件复制为`c`文件来用`clang`编译   

### 思考题
请在`report/report.md`中详细回答下述思考题：
1-1 请给出while语句对应的LLVM IR的代码布局特点，重点解释其中涉及的几个`br`指令的含义（包含各个参数的含义）
1-2 请简述函数调用语句对应的LLVM IR的代码特点
