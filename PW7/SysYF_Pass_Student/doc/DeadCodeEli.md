## 死代码删除

### 任务描述

#### 任务1

你需要补充`include/Optimize/DeadCodeEli.h`和`src/Optimize/DeadCodeEli.cpp`中的`DeadCodeEli`类，来实现一个完整的过程内死代码删除算法，注意：该算法基于**SSA**形式的CFG。`DeadCodeEli`类中的`execute`函数会被调用来执行你实现的死代码删除算法，你需要将你的实现流程体现在该函数中（可以参考`Mem2Reg.cpp`和`DominateTree.cpp`）。

#### 任务2

在实验报告中回答下列问题：
1. 请说明你实现的死代码删除算法的设计思路。

### 实验提示Tips

- 可以参考`Mark and Sweep`算法，参考资料：[DeadCodeEli.pdf](DeadCodeEli.pdf)。相关资料来自《Engineering a Compiler》；
- 在实验框架中提供了反向支配树的相关接口，有需要的话可以使用。

### 反向支配树接口相关说明

反向支配树的相关接口在`include/SysYFIR/BasicBlock.h`中。每个BasicBlock有两个属性：`rdoms_`和`rdom_frontier_`，分别表示当前基本块的反向支配节点集合与反向支配边界(类似支配节点集合与支配边界)。以下两个接口你需要使用：

- `get_rdoms`接口返回当前基本块的反向支配基本块集合
- `get_rdom_frontier`返回当前基本块的反向支配边界

此外， `add_rdom_frontier`、`clear_rdom_frontier`、`add_rdom`、`clear_rdom`是用于维护反向支配关系的接口，这些接口在`src/Optimize/RDominateTree.cpp`中被使用，你们不需要关心。

若要使用反向支配关系，需要手动进行计算，例如
```cpp
    #include "RDominateTree.h"
    // ...
    RDominateTree r_dom_tree(module);   // 名字可以随便起
    r_dom_tree.execute();
```
