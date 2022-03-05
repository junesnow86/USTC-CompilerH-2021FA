# PW6 实验文档
- [PW6 实验文档](#pw6-实验文档)
  - [0. 前言](#0-前言)
    - [主要工作](#主要工作)
  - [1. 实验要求](#1-实验要求)
    - [1.1 目录结构](#11-目录结构)
    - [1.2 提交要求和评分标准](#12-提交要求和评分标准)
## 0. 前言

本次实验分为3关，为组队实验。**本次实验请务必使用git提交**。    
本次实验的目的是让大家熟悉生成中间代码所需要的相关知识: LLVM IR、 SysYF IR（LLVM IR的轻量级C++接口），并实际实现一个IR Builder。
在开始实验之前，请确保LLVM的版本不低于10.0.1，且PATH环境变量配置正确。可以通过`lli --version`命令是否可以输出10.0.1的版本信息来验证。

### 主要工作

1. 第一部分: 了解LLVM IR。通过clang生成的.ll，了解LLVM IR与c代码的对应关系。相应文档见[phase1.md](./doc/phase1.md)
2. 第二部分: 了解SysYF IR。通过助教提供的c++例子，了解SysYF IR的c++接口及实现。相应文档见[phase2.md](./doc/phase2.md)
3. 第三部分: 使用SysYF IR，实现一个IR Builder，使其可以通过抽象语法树生成LLVM兼容的IR代码。相应文档见[phase3.md](./doc/phase3.md)
4. 实验报告：在[report.md](./report/report.md)中撰写报告。

## 1. 实验要求

### 1.1 目录结构
除了下面指明你所要修改或提交的文件，其他文件请勿修改。
``` log
.
├── CMakeLists.txt
├── README.md                           <- 实验文档说明（你在这里）
├── doc
│   ├── AST.md
│   ├── phase1.md                       <- 各阶段文档
│   ├── phase2.md
│   ├── phase3.md
│   ├── SysYF语言定义.pdf
|   └── SysYFIR.md                      <- SysYF IR 应用编程接口相关文档
├── report
│   ├── report.md                       <- 需提交的实验报告
│   └── contribution.md                 <- 需提交的组员贡献（队长负责填写）
├── include                             <- 实验所需的头文件
│   ├── ...
│   └── SysYFIR
├── src
│   ├── ...
│   ├── SysYFIR
│   └── SysYFIRBuilder
|       ├── CMakeLists.txt
|       └── IRBuilder.cpp               <- 你需要在第三关任务中修改的文件
└── Student
    ├── task1						   <- 第一关任务相关的目录
    |   ├── ll                          <- 需提交的LLVM IR文件(.ll)的目录（第一关）
    |   |   ├── assign_hand.ll
    |   │   ├── fun_hand.ll
    |   │   ├── if_hand.ll
    |   │   └── while_hand.ll
    |   ├── sy
    |   |   ├── assign_test.sy
    |   │   ├── fun_test.sy
    |   │   ├── if_test.sy
    |   │   └── while_test.sy
    |   └── demo
    |       └── go_upstairs.c
    ├── task2						   <- 第二关任务相关的目录
    ├── CMakeLists.txt
    |   ├── cpp                         <- 需提交的.cpp目录（第二关）
    |   |   ├── CMakeLists.txt
    |   |   ├── assign_gen.cpp
    |   │   ├── fun_gen.cpp
    |   │   ├── if_gen.cpp
    |   │   └── while_gen.cpp
    |   ├── sy
    |   |   ├── assign_test.sy
    |   │   ├── fun_test.sy
    |   │   ├── if_test.sy
    |   │   └── while_test.sy
    |   └── demo
    |       |── CMakeLists.txt
    |       |── go_upstairs.sy
    |       └── go_upstairs_gen.cpp     <- 打印go_upstairs.ll的cpp文件
    └── task3
        └── test
            ├── test.py                 <- 第三关任务的评测脚本
            └── test                    <- 测试样例文件夹
```

### 1.2 提交要求和评分标准
* 提交要求  
  本实验的提交要求分为两部分: 实验部分的文件和报告。
  * 实验部分:
    * 需要完成 `./Student/task1/ll`目录下的4个文件
    * 需要完成 `./Student/task2/cpp`目录下的4个文件
    * 需要完成 `./src/SysYFIRBuilder/IRBuilder.cpp`
    * 需要在 `./report/report.md` 中撰写实验报告
      * 实验报告内容包括:
        * 实验要求、问题回答、实验设计、实验难点及解决方案、实验总结、实验反馈、组间交流(具体参考[report.md](./report.md))
        * 本次实验报告**参与**评分标准.
  * 提交规范: 
    * 不破坏目录结构(`report.md`如果需要放图片，请新建`figs`文件夹放在`./report`下，并将图片放在`figs`文件夹内)
    * 不上传临时文件(凡是自动生成的文件和临时文件请不要上传)
* **组队实验要求**
  * 由队长在 `./report/contribution.md` 中解释每位队员的贡献，并说明贡献比例
  * 组队实验意味着合作，但是小组间的交流是受限的，且**严格禁止**代码的共享。除此之外，如果小组和其它组进行了交流，必须在 `./report/report.md` 中记录交流的小组和你们之间交流内容
* 评分标准: 本次实验分为3部分, 为组队实验, 请合理安排分工, 我们会根据组长填写的贡献比进行分数分配，如果对贡献比有异议的组员可根据git的提交记录申请仲裁，建议利用好git的分支功能
  * **禁止执行恶意代码，违者本次实验0分处理**
  * 第一部分10分: `.ll`运行结果正确(1个2分, 注释共2分)
  * 第二部分20分: `.cpp`运行结果正确(1个5分)
  * 第三部分70分: 该部分成绩由5部分组成(团队代码得分, 实验报告得分, 迟交天数, 组员贡献比, 组长奖励加分)
* 实验检查
  * 线上: 助教会在educoder上检查前两部分
  * 线下: 线下检查只检查第三部分, 组长带组员到负责组长的助教处检查, 选做部分请找本次实验负责助教检查
* 迟交规定
  * 迟交需要邮件通知助教: 
    * 邮箱: huangzq@mail.ustc.edu.cn
    * 邮件主题: PW6迟交-学号
    * 内容: 包括迟交原因、最后版本commit ID、迟交时间等
* 关于抄袭和雷同
  经过助教和老师判定属于作业抄袭或雷同情况，所有参与方一律零分，不接受任何解释和反驳。
如有任何问题，欢迎提issue进行批判指正。
