__dynamic_cast__

1. for循环作用是计算 `values` 列表中有效指令(单操作数指令和两个操作数的指令)的条数，通过使用 `dynamic_cast` (这里使用了RTTI)来判断 `v` 是否实际上指向了 `UnaryInst` 或者 `BinaryInst` 对象，如果不是就会导致 `dynamic_cast` 转换失败而返回 `nullptr`。
2. 将代码中的 `if(dynamic_cast<UnaryInst *>(v))` 换成 `if(v.getname() == std::string("UnaryInst"))`，同样处理 `BinaryInst` 的部分。
3. 在 `BasicBlock::print` 中创建一个 `vector<string>` 用于记录所有 `Instruction` 子类和一个 `vector<int>` 用于记录每种子类的数目(vector 支持[]操作符，可以用下标将两个 vector 联系起来)，每次检查 `values` 列表中的元素时先判断是否已在 `vector<string>` 中，如果已在就令 `vector<int>` 相应项自增，如果不在就在 `vector<string>` 中新增一项，在 `vector<int>` 中新增一项(初始化为1)。

__typeid__

1. gcc 编译，程序运行后输出如下：

    ```
    P5Value			// P 表示指针，v是一个指向 Value(5个字符) 类型对象的指针
    10BasicBlock	// (*v)是一个 BasicBlock(10个字符) 类型对象
    P11Instruction	// inst是一个指向 Instruction(11个字符) 类型对象的指针
    10BinaryInst	// (*inst)是一个 BianryInst(10个字符) 类型对象
    ```

2. 去掉 `Instruction` 的父类后输出如下：

    ```
    P5Value			
    10BasicBlock	
    P11Instruction	
    11Instruction	// !
    ```

    产生的区别是 (*inst) 是一个 `Instruction` 对象，而不是第一问中的 `BinaryInst`，原因是 `Value` 类中含有一个虚析构函数，`Value` 类具有多态性，没有去掉对 `Value` 类的继承的时候 `typeid` 操作符返回表达式的动态类型(根据运行时 inst 指向的实际类型计算)，比如 `BasicBlock` 没有去掉对 `Value` 的继承，`typeid (*v)` 就返回 (\*v) 运行时的类型；但是当 `Instruction` 类没有继承 `Value` 类时，自己本身也没有虚函数，不具有多态性，(\*inst) 将会采用编译时期类型来计算，而编译时期它是 `Instruction` 对象，`typeid (*inst)` 返回静态类型(编译时直接根据 inst 的指针类型计算)。   

