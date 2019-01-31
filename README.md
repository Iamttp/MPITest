# MPI测试程序

> MPI实现并行是进程级；采用的是分布式内存系统，显式（数据分配方式）实现并行执行，通过通信在进程之间进行消息传递，可扩展性好。MPI虽适合于各种机器，但它的编程模型复杂：

* 需要分析及划分应用程序问题，并将问题映射到分布式进程集合；
* 需要解决通信延迟大和负载不平衡两个主要问题；
* 调试MPI程序麻烦；
* MPI程序可靠性差，一个进程出问题，整个程序将错误；

## 目录
#### 1.点到点通信，简单测试MPI：
* [MPI_Point_1](/MPI_Point_1/index.md)
#### 2.集合通信，并行化梯形积分法：
* [MPI_Collective_1](/MPI_Collective_1/index.md)
#### 3.点到点通信，随机漫步并行化实现：
* [MPI_Random_Walk](/MPI_Random_Walk/index.md)