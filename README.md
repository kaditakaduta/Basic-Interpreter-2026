# Basic-Interpreter-2026

## 目录

- [简介](#1)
  - [背景](#2)
  - [作业目标](#3)
- [作业要求](#4)
  - [基础任务](#5)
      - [下发文件](#6)
      - [解释器实现步骤及待实现文件介绍](#7)
      - [实现要求](#8)
  - [bonus](#9)
- [须知](#10)
  - [Deadline](#11)
  - [本地评测](#12)
  - [OJ评测](#13)
  - [评分细则](#14)
- [负责助教](#15)
- [Special Thanks](#16)


##  简介

### 背景

BASIC 是一门**解释性**编程语言，本次大作业要求你用 C++ 实现这个语言中的一些功能，来完成一个 Minimal 版本的 BASIC 解释器。

该解释器具有的功能有：

- **立即解释**某些语句并运行
- 执行特定控制语句
- 按照行数升序依次运行的大程序

### 作业目标

- 锻炼文档的阅读能力
- 初步了解解释器的设计
- 锻炼 git 的使用

## 作业要求

### 基础任务

#### 下发文件

```plain
├── docs/
├── src/
│   ├── utils/
│   │   └── Error.cpp
│   ├── Basic.cpp
│   ├── Expression.cpp
│   ├── Lexer.cpp
│   ├── Parser.cpp
│   ├── Program.cpp
│   ├── Recorder.cpp
│   ├── Statement.cpp
│   ├── Token.cpp
│   └── VarState.cpp
├── include/
│   ├── utils/
│   │   └── Error.hpp
│   ├── Expression.hpp
│   ├── Lexer.hpp
│   ├── Parser.hpp
│   ├── Program.hpp
│   ├── Recorder.hpp
│   ├── Statement.hpp
│   ├── Token.hpp
│   └── VarState.hpp
├── test/
├── Basic-Demo-64bit
├── CMakeLists.txt
├── .gitignore
├── README.md
├── ScopeTest.cpp
└── AttachedTest.cpp
```

#### 解释器实现说明

**对于指令的介绍和要求详见 `docs/Minimal-BASIC-Interpreter-2023.pdf`** 。
**项目的整体框架详见 [项目文档](docs/Framework.md)**。
对于各个文件的具体职责和要求详见`docs/`下的各个模块文档。
对于bonus的部分详见`docs/Bonus.md`。
你需要完成`include/`和`src/`下的头文件和源文件中的 TODO 部分。

#### 实现要求

我们会进行基本的**鲁棒性检测**和**内存泄漏检测**，但是不进行性能检测，你只需要通过下发的数据点即可。

## 须知

### Deadline
12.3 19:00

### 本地评测
```
├── Basic-Demo-64bit
├── CMakeLists.txt
├── test
├── AttachTest.cpp
└── ScopeTest.cpp
```

#### 评测数据

`test/` 文件夹中的 100 个数据点，与 OJ 中测评的数据点完全一致。

对于 bonus 中 Scope 嵌入部分另有 `test/scoped/` 文件夹中 16 个数据点，也与 OJ 上一致。

OJ 评测会有另外的 20 个高强度隐藏测试点。

#### 评测原理

与标程对拍 （指进行相同输入看输出是否相同）

#### 标程

如果你用的是 wsl 或 linux ，请删除 `Basic-Demo-64bit-For-Mac` 。

如果你用的是 mac ，请删除 `Basic-Demo-64bit` ，并将 `Basic-Demo-64bit-For-Mac` 改名为 `Basic-Demo-64bit` 。

之后的步骤中我们认为你完成了此操作。

`Basic-Demo-64bit` 是标程的可执行文件，你可以用命令行输入 `./Basic-Demo-64bit` 来运行它，看看 BASIC 解释器是如何工作的。

【注：如果你在wsl下运行 `./Basic-Demo-64bit` 时出现 Permission denied 错误，可以运行 `chmod +x Basic-Demo-64bit` 来修改权限。】

#### 评测脚本使用方法

使用 CMake 构建，然后运行编译产生的可执行文件 attached_test（测试 basic 部分）、scope_test（测试 bonus 部分）即可进行本地测试。

【注意：如果你修改了仓库中给出框架的文件结构，请相应修改 `AttachedTest.cpp` 与 `ScopeTest.cpp` 中通过常量输入的相关文件路径，否则无法正常进行本地测试。】

### OJ 评测

你需要使用git进行版本管理和代码提交。比如，你的git仓库地址是 `Your_profile/Your_repo`，你只需要在OJ的提交页面中输入 `https://github.com/Your_profile/Your_repo` 即可。

**注意，你的可执行文件的名字必须为 `code`（如果你修改了CMake，请务必保证可执行文件名仍为 `code` ）。**

测评文件内容默认是 Test 文件夹下提供的文件。这些文件和 OJ 中测评的数据点是相同的。在这些测试点下，你的程序需要输出与标程相同的结果。

### 评分细则

- 基础任务 60%
  - 按 OJ 得分给分
- 隐藏测试点 20%
  - 按 OJ 得分给分
- Code Review 20%
- 使用智能指针 3% (bonus)
- 实现 Scope 嵌入 5% (bonus)

## 负责助教

[@赵睿城](https://github.com/TfOi9)，[@刘劢辰](https://github.com/lmc070222)

## Special Thanks

感谢 22' ACM HenryHe0123, 22' ACM Irfnfnkemed 提供的文档 `Minimal-BASIC-Interpreter-2023.pdf` 。

感谢 23' ACM [@李林璋](https://github.com/Seven-Streams)，[@王思瀚](https://github.com/leowang000)，[@李方可](https://github.com/algebraic-arima) 提供的代码实现参考。

感谢 25' ACM [@卓翔](https://github.com/zxsheather)，[@葛仁澍](https://github.com/TOmorrowarc1) 对本项目的重构。
