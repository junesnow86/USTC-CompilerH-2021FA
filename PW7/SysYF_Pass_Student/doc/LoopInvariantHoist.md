## 循环不变式外提

### 任务描述

#### 任务1

你需要补充`include/Optimize/LoopInvariant.h`和`src/Optimize/LoopInvariant.cpp`中的`LoopInvariant`类，来实现一个完整的循环不变式外提算法，注意：该算法基于**SSA**形式的CFG。  
本次实验中，你需要完成的部分包括：  
1. 寻找每个函数内的循环
2. 寻找每个循环中的循环不变式
3. 将循环不变式外提

`LoopInvariant`类中的`execute`函数会被调用来执行你实现的循环不变式外提算法，你需要将你的实现流程体现在该函数中。  

#### 任务2

在实验报告中回答下列问题：
1. 请说明你实现的循环不变式外提算法的设计思路。

### Tips

- 循环可以根据强连通分量判断，可以利用[Tarjan算法](https://en.m.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)来寻找；

- 思考如何判断语句与循环无关，且外提没有副作用；

- 循环不变式应该外提到循环入口基本块的前驱，但循环入口基本块会有多个前驱，思考循环不变式应该外提到哪一个前驱。
