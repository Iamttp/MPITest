# 三、MPI_Random_Walk--随机漫步并行化实现：

## 1.编译：
```
mpicxx -g -Wall -o mpi_hello.o main1.cpp 
``` 

## 2.运行及结果：
> 编译完成后，开始运行，可由-n后面的数字来调节创
建进程数。
```
mpirun -n 4 ./mpi_hello.o
```
```
Process 0 initiated 20 walkers in subdomain 0 - 24
Process 0 sending 12 outgoing walkers to process 1
Process 1 initiated 20 walkers in subdomain 25 - 49
Process 1 sending 9 outgoing walkers to process 2
Process 2 initiated 20 walkers in subdomain 50 - 74
Process 2 sending 9 outgoing walkers to process 3
Process 3 initiated 20 walkers in subdomain 75 - 99
Process 1 received 12 incoming walkers
Process 2 received 9 incoming walkers
Process 2 sending 0 outgoing walkers to process 3
Process 1 sending 0 outgoing walkers to process 2
Process 2 received 0 incoming walkers
Process 2 sending 0 outgoing walkers to process 3
Process 3 sending 9 outgoing walkers to process 0
Process 3 received 9 incoming walkers
Process 0 received 9 incoming walkers
Process 0 sending 0 outgoing walkers to process 1
Process 2 received 0 incoming walkers
Process 2 done
Process 1 received 0 incoming walkers
Process 1 sending 0 outgoing walkers to process 2
Process 3 sending 0 outgoing walkers to process 0
Process 0 received 0 incoming walkers
Process 0 sending 0 outgoing walkers to process 1
Process 1 received 0 incoming walkers
Process 1 done
Process 0 received 0 incoming walkers
Process 0 done
Process 3 received 0 incoming walkers
Process 3 sending 0 outgoing walkers to process 0
Process 3 received 0 incoming walkers
Process 3 done
```

## 3.备注：
##### 注意：
* 详情参见链接：http://mpitutorial.com/tutorials/point-to-point-communication-application-random-walk/
* 源代码可能会产生 prevention(死锁)
* 考虑输入输出可能出现的问题
##### 重要：
* 注意学习源代码如何传递的结构体（利用MPI_probe、MPI_Get_count）。
```cpp
int MPI_probe(int source,int tag,MPI_Comm comm,MPI_Status *status)
    IN      source      发送消息进程的编号
    IN      tag         接收消息的标签
    IN      comm      通信子
    OUT    status       返回到消息的状态
int MPI_Get_Count(MPI_Status status,MPI_Datatype datatype,int *count)
    IN      status      接收消息时返回的状态
    IN      datatype    接收消息时返回的类型
    OUT    Count       接收消息时数组元素的个数
```
* 该代码主要描述，在不同子域产生总计100（可修改）的Walker，
  Walker由一个结构体定义，描述了当前位置和可以的运行步数（随机，小于max_walk_size（50可更改））。
  在一次按照运行步数最大推出的循环次数内，进行循环，并考虑用任务划分来
