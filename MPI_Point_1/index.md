# 一、MPI_Point_1--简单测试MPI:	
## 1.编译：
```
mpicxx -g -Wall -o mpi_hello.o main1.cpp 
``` 
> mpicc         是编译C程序的
> 
> mpicxx        是编译C++程序的
> 
> -g            允许使用调试器
> 
> -Wall         显示警告（W大写）
> 
> -o outfile.o  编译出可执行的文件，文件名为outfile.o
> 
> -02           告诉编译器对代码进行优化


## 2.运行：
```
mpirun -n 4 ./mpi_hello.o
``` 
> 编译完成后，开始运行，可由-n后面的数字来调节创建进程数。


## 3.运行结果：
> Greetings from process 0 of 4!
> 
> Greetings from process 1 of 4!
> 
> Greetings from process 2 of 4!
> 
> Greetings from process 3 of 4!

## 4.记录：
* SPMD（单程序多数据流）程序
* 分布式内存系统编程 (进程通信)

    *OMPI_DECLSPEC int MPI_Send(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)*

	*OMPI_DECLSPEC int MPI_Recv(void * buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status * status)*
1. 前三个参数定义了消息的内容，剩下的参数定义了消息的目的地
2. dest/source 接受消息的进程号 
3. tag 非负int，区分不同的消息
4. comm 通信子，指定通信范围 
