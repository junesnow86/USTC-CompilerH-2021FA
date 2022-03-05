[TOC]

---

### 任务描述
**本关任务**：熟悉SysYF IR的应用编程接口，并根据给出的4个SysYF程序手写调用SysYF IR应用编程接口的C++代码，生成与sy文件功能相同的ll文件。

### 相关知识
#### SysYF IR 应用编程接口
由于LLVM IR官方的C++应用编程接口的文档内容繁多，本实训项目提供SysYF IR应用编程接口库，该库用C++编写，可以用于生成LLVM IR的子集。你需要阅读**SysYF IR核心类的介绍**`doc/SysYFIR.md`。  
本关要求你根据AST，使用SysYF IR应用编程接口来构建生成LLVM IR。你需要先仔细阅读文档`doc/SysYFIR.md`以了解其接口的设计。

#### 样例学习
<details>
  <summary> go_upstairs_gen.cpp核心部分（点击展开） </summary>

```cpp
    // 全局数组,num,x
    auto *arrayType_num = ArrayType::get(Int32Type, 2);
    auto *arrayType_x = ArrayType::get(Int32Type, 1);
    auto zero_initializer = ConstantZero::get(Int32Type, module);
    std::vector<Constant *> init_val;
    init_val.push_back(CONST_INT(4));
    init_val.push_back(CONST_INT(8));
    auto num_initializer = ConstantArray::get(arrayType_num, init_val);
    auto num = GlobalVariable::create("num", module, arrayType_num, false, num_initializer);//          是否是常量定义，初始化常量(ConstantZero类)
    auto x = GlobalVariable::create("x", module, arrayType_x, false, zero_initializer);// 参数解释：  名字name，所属module，全局变量类型type，

    auto n = GlobalVariable::create("n", module, Int32Type, false, zero_initializer);
    auto tmp = GlobalVariable::create("tmp", module, Int32Type, false, CONST_INT(1));

    // climbStairs函数
    // 函数参数类型的vector
    std::vector<Type *> Ints(1, Int32Type);

    //通过返回值类型与参数类型列表得到函数类型
    auto climbStairsFunTy = FunctionType::get(Int32Type, Ints);

    // 由函数类型得到函数
    auto climbStairsFun = Function::create(climbStairsFunTy,
                                    "climbStairs", module);

    // BB的名字在生成中无所谓,但是可以方便阅读
    auto bb = BasicBlock::create(module, "entry", climbStairsFun);

    builder->set_insert_point(bb);                        // 一个BB的开始,将当前插入指令点的位置设在bb

    auto retAlloca = builder->create_alloca(Int32Type);   // 在内存中分配返回值的位置
    auto nAlloca = builder->create_alloca(Int32Type);     // 在内存中分配参数n的位置

    std::vector<Value *> args;  // 获取climbStairs函数的形参,通过Function中的iterator
    for (auto arg = climbStairsFun->arg_begin(); arg != climbStairsFun->arg_end(); arg++) {
    args.push_back(*arg);   // * 号运算符是从迭代器中取出迭代器当前指向的元素
    }

    builder->create_store(args[0], nAlloca);  // store参数n

    auto retBB = BasicBlock::create(
        module, "", climbStairsFun);  // return分支,提前create,以便true分支可以br

    auto nLoad = builder->create_load(nAlloca);           // 将参数n load上来
    auto icmp = builder->create_icmp_lt(nLoad, CONST_INT(4));  // n和4的比较,注意ICMPLT

    auto trueBB = BasicBlock::create(module, "trueBB_if", climbStairsFun);    // true分支
    auto falseBB = BasicBlock::create(module, "falseBB_if", climbStairsFun);  // false分支

    builder->create_cond_br(icmp, trueBB, falseBB);  // 条件BR
    DEBUG_OUTPUT // 我调试的时候故意留下来的,以醒目地提醒你这个调试用的宏定义方法
    builder->set_insert_point(trueBB);  // if true; 分支的开始需要SetInsertPoint设置
    nLoad = builder->create_load(nAlloca);
    builder->create_store(nLoad, retAlloca);
    builder->create_br(retBB);  // br retBB

    builder->set_insert_point(falseBB);  // if false
    auto *arrayType_dp = ArrayType::get(Int32Type, 10);
    auto dpAlloca = builder->create_alloca(arrayType_dp);

    auto dp0Gep = builder->create_gep(dpAlloca, {CONST_INT(0), CONST_INT(0)});
    builder->create_store(CONST_INT(0), dp0Gep);

    auto dp1Gep = builder->create_gep(dpAlloca, {CONST_INT(0), CONST_INT(1)});
    builder->create_store(CONST_INT(1), dp1Gep);

    auto dp2Gep = builder->create_gep(dpAlloca, {CONST_INT(0), CONST_INT(2)});
    builder->create_store(CONST_INT(2), dp2Gep);

    auto iAlloca = builder->create_alloca(Int32Type);
    builder->create_store(CONST_INT(3), iAlloca);

    auto condBB = BasicBlock::create(module, "condBB_while", climbStairsFun);  // 条件BB
    trueBB = BasicBlock::create(module, "trueBB_while", climbStairsFun);    // true分支
    falseBB = BasicBlock::create(module, "falseBB_while", climbStairsFun);  // false分支

    builder->create_br(condBB);

    builder->set_insert_point(condBB);
    //后略, 详细见代码文件
```
</details>

为了更直观地感受并学会使用 SysYF IR应用编程接口，本实训项目提供了示例代码，位于`Student/task2/demo/go_upstairs_gen.cpp`。  
该C++程序会生成与go_upstairs.c逻辑相同的LLVM IR文件，在该C++程序中提供了详尽的注释，请阅读理解，以便更好地开展你的实验！  

### 本关具体任务
1. 你需要在`Student/task2/cpp/`文件夹中，调用SysYF IR应用编程接口，编写自己的 `assign_gen.cpp`，`func_gen.cpp`，`if_gen.cpp`，`while_gen.cpp`程序，以生成与第1关的四个sy 程序相同逻辑功能的ll文件。
2. 在`report.md`内回答[思考题](#思考题)

### 编译、运行和验证
在 `Student/task2/build/` 下执行:
``` shell
# 如果存在 CMakeCache.txt 要先删除
# rm CMakeCache.txt
cmake ..
make
```
你可以得到对应 `assign_gen.cpp`，`func_gen.cpp`，`if_gen.cpp`，`while_gen.cpp`，`go_upstairs_gen.cpp`的可执行文件`assign_generator`，`func_generator`，`if_generator`，`while_generator`，`go_upstairs_generator`。  
之后直接执行可执行文件，即可得到对应的ll文件：  
``` shell
# 在build文件夹内
./go_upstairs_generator
```

### 思考题
请在`report/report.md`中详细回答下述思考题：

2-1. 请给出`SysYFIR.md`中提到的两种getelementptr用法的区别, 并解释原因:
  - `%2 = getelementptr [10 x i32], [10 x i32]* %1, i32 0, i32 %0` 
  - `%2 = getelementptr i32, i32* %1, i32 %0`