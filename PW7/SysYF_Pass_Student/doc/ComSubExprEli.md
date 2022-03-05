## 公共子表达式删除

### 任务描述

#### 任务1

你需要补充`include/Optimize/ComSubExprEli.h`和`src/Optimize/ComSubExprEli.cpp`中的`ComSubExprEli`类，来实现一个完整的过程内全局公共子表达式删除算法，该算法基于**SSA**形式的控制流图（CFG）。`ComSubExprEli`类中的`execute`函数会被调用来执行你实现的公共子表达式删除算法，你需要将你的实现流程体现在该函数中（可以参考`Mem2Reg.cpp`和`DominateTree.cpp`）。在本关中，公共子表达式删除的对象不包括：void指令、call指令、phi指令、alloca指令、load指令和cmp指令。可以见`static bool ComSubExprEli::is_valid_expr(Instruction *inst)`：

```cpp
bool ComSubExprEli::is_valid_expr(Instruction *inst) {
    return !(inst->is_void()||inst->is_call()||inst->is_phi()||inst->is_alloca()||inst->is_load()||inst->is_cmp());
}
```
该函数用于判断一条指令是否应该列入公共子表达式删除的考虑范围。

#### 任务2

在实验报告中回答下列问题：
1. 请说明你实现的公共子表达式删除算法的设计思路。
2. 若要将call指令、load指令列入公共子表达式删除的考虑范围，除了你实现的公共子表达式删除算法，还需要考虑哪些其他因素？

### 实验提示(Tips)

1. 公共子表达式删除需要利用可用表达式分析的结果;
2. 本次实验提供的CFG均为`SSA`形式。现有的公共子表达式删除和可用表达式分析算法一般是针对非SSA形式的通用情况，而针对SSA形式的算法可以适当简化。
