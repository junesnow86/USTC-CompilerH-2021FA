## 活跃变量分析

### 任务描述

#### 任务1

你需要补充`include/Optimize/ActiveVar.h`和`src/Optimize/ActiveVar.cpp`中的`ActiveVar`类，来实现一个完整的活跃变量分析算法，分析所有`BasicBlock`块入口和出口的活跃变量集合，注意：该算法必须是基于**SSA**形式的CFG。  
在本次实验的框架中,`BasicBlock`类实现了4个和活跃变量分析相关的函数，你需要调用它们，设置所有`BasicBlock`入口与出口处的活跃变量集合，以完成实验：  
```cpp
// 设置该BasicBlock入口处的活跃变量集合
void set_live_in(std::set<Value*> in){live_in = in;}
// 设置该BasicBlock出口处的活跃变量集合
void set_live_out(std::set<Value*> out){live_out = out;}
// 获取该BasicBlock入口处的活跃变量集合
std::set<Value*>& get_live_in(){return live_in;}
// 获取该BasicBlock出口处的活跃变量集合
std::set<Value*>& get_live_out(){return live_out;}
```
`ActiveVar`类中的`execute`函数会被调用来执行你实现的活跃变量分析算法，你需要将你的实现流程体现在该函数中。  

#### 任务2

在实验报告中回答下列问题
1. 请说明你实现的活跃变量分析算法的设计思路。

### 实验提示(Tips)

和上课时所讲的活跃变量分析不同，本次实验的活跃变量分析需要考虑phi指令，而数据流方程：$\rm OUT[B] =\cup_{S是B的后继}IN[S]$ 的定义蕴含着基本块S入口处活跃的变量在基本块S所有前驱的出口处都是活跃的。  
由于`phi`指令的特殊性，例如`%0 = phi [%op1, %bb1], [%op2, %bb2]`如果使用如上数据流方程，则默认此`phi`指令同时产生了`op1`与`op2`的活跃性，而事实上只有控制流从`%bb1`传过来才有`%op1`的活跃性，从`%bb2`传过来才有`%op2`的活跃性。因此你需要对此数据流方程做一些修改。
   
