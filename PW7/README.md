- [SysYFCodeGenOpt](#sysyfcodegenopt)
  - [介绍](#介绍)
  - [概述](#概述)
  - [任务说明](#任务说明)
    - [必做部分](#必做部分)
    - [选做部分](#选做部分)
      - [选题1-进阶优化](#选题1-进阶优化)
      - [选题2-运行时空间管理与代码生成](#选题2-运行时空间管理与代码生成)
      - [选题3-低级中间代码(LIR)生成](#选题3-低级中间代码lir生成)
      - [选题4-自由发挥](#选题4-自由发挥)
    - [本实验设计及软件包的研发者](#本实验设计及软件包的研发者)
  - [特技](#特技)
# SysYFCodeGenOpt

## 介绍
本项目提供SysYF语言的中间表示(IR)优化以及代码生成的编译器实践框架和选题。SysYF语言是全国编译系统设计赛要求实现的SysY语言的扩展语言，SysYF IR兼容LLVM IR。该项目由中国科学技术大学张昱老师研究组设计和开发，旨在引导更多学生和社会人员学习和实践编译器相关知识，开展语言设计与实现、程序分析、编译优化等研发，让越来越多的人有能力运用程序语言基础提供可靠、高效的软件解决方案。

## 概述

- **分组实验**：大实验以组为单位，分组与上次实验相同。
- **公开仓库**：各组自行在[gitee](https://gitee.com/)上建库并fork该仓库。
- **小组任务**：各组需要完成下面的**必做项**，另外从**选做项**中选择一项开展。
- **实验提交**：各组需要在2021-12-25 22:00:00前在助教处登记gitee仓库地址以及选题，助教会取截止日期前的最后一次commit记录作为最终的提交。
- **时间安排**：实验时间初步定为2021-12-20 - 2022-01-10 23:59:59。答辩日期定为2022-01-12

## 任务说明

本次实验分为必做部分和选做部分。你需要完成必做的全部内容并在选做的若干个选题中选择一个来做。你还需要完成一份实验报告，讲述你所做的工作。

### 必做部分

必做部分文件夹在[SysYF_Pass_Student](SysYF_Pass_Student/)

### 选做部分

你需要在以下选题中选择一个来做。

#### 选题1-进阶优化

该部分负责助教为吴毓辰、黄庄湫。该部分文件夹依旧在[SysYF_Pass_Student](SysYF_Pass_Student/)
在必做优化的基础上，你需要在以下三种优化中选择两种来做：循环不变式外提、常量传播、死代码删除。对应文档分别见[LoopInvariantHoist.md](SysYF_Pass_Student/doc/LoopInvariantHoist.md)、[ConstPropagation.md](SysYF_Pass_Student/doc/ConstPropagation.md) 和[DeadCodeEli.md](SysYF_Pass_Student/doc/DeadCodeEli.md)。在实验报告中你需要**自行构造并提交测试程序**以展示所开展优化的效果和特色。

#### 选题2-运行时空间管理与代码生成

该部分负责助教为王原龙、陈金宝。该部分文件夹在[SysYF_Backend_Student](SysYF_Backend_Student/)

详细文档见[PW7-backend.md](SysYF_Backend_Student/doc/PW7-backend.md)。

#### 选题3-低级中间代码(LIR)生成

该部分负责助教为万嘉诚。该部分文件夹在[BZ_Backend_Student](BZ_Backend_Student/)

详细文档见[README.md](BZ_Backend_Student/README.md)。

#### 选题4-自由发挥

你也可以不做以上的三个选题，做你认为有意义的选题。但需要在实验报告、答辩中详细阐述你所做的工作。

### 本实验设计及软件包的研发者

   本实验由中国科学技术大学计算机科学与技术学院张昱老师和承担2021年秋季学期《编译原理和技术(H)》、《编译原理和技术》（网安英才班）的6位助教（2018级本科生）研讨而设计，并由6位助教实现（分工如下）。实验软件包中如有不当或问题，欢迎反馈。

- 必做部分
  - 陈金宝：公共子表达式删除
  - 吴毓辰：活跃变量分析
  - 吴钰同：支配关系
- 选题1-进阶优化
  - 吴毓辰、黄庄湫：循环不变式外提、常量传播、死代码删除
- 选题2-运行时空间管理与代码生成
  - 王原龙、陈金宝
- 选题3-低级中间代码(LIR)生成
  - 万嘉诚


## 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
