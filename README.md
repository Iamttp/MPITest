# MPI测试程序

> MPI实现并行是进程级；采用的是分布式内存系统，显式（数据分配方式）实现并行执行，通过通信在进程之间进行消息传递，可扩展性好。MPI虽适合于各种机器，但它的编程模型复杂：

* 需要分析及划分应用程序问题，并将问题映射到分布式进程集合；
* 需要解决通信延迟大和负载不平衡两个主要问题；
* 调试MPI程序麻烦；
* MPI程序可靠性差，一个进程出问题，整个程序将错误；


# 一、Test--简单测试MPI:	
## 1.编译：
>  mpicxx -g -Wall -o mpi_hello.o main1.cpp 
> 
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
> -n 4 ./mpi_hello.o
> 
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

# 二、MPI2--并行化梯形积分法:
## 伪代码：
	/* 串行程序伪代码 */
 	/* input a,b,n  n:划分段数*/
 	h = (b-a)/n;
	approx = ( f(a) + f(b) ) / 2.0
	for(i=1; i<=n-1; i++)
	{
		approx += f( a + i*h );
	}
	approx = h*approx;

## main1.cpp--版本1 编译：
> mpicxx -g -Wall -o mpi_hello.o main1.cpp 

## 运行及结果：
> 编译完成后，开始运行，可由-n后面的数字来调节创
建进程数。
>
> mpirun -n 4 ./mpi_hello.o

> With n = 1024 trapezoids, our estimate
> 
> of the integral from 0.000000 to 3.000000 = 1.148197004588656e+01

## main2.cpp--版本2(加入数据输入和改用集合通信)：
> 在MPI中，涉及所有的进程的通信函数我们称之为集合通信（collective communication）。而单个进程对单个进程的通信，类似于MPI_Send和MPI_Recv这样的通信函数，我们称之为点对点通信（point-to-point communication）。

#### 特点
1. 在通信子中的所有进程都必须调用相同的集合通信函数。
2. 每个进程传递给MPI集合通信函数的参数必须是“相容的”。
3. 点对点通信函数是通过标签和通信子来匹配的。而通信函数不实用标签，只是通过通信子和调用的顺序来进行匹配。

![avatar](1.png)

#### 参数对比
> 集合通信 MPI_Reduce：
> 
> (const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
> 
> 点对点通信 MPI_Send：
> 
> (const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)

## 记录
###### MPI_Allreduce和MPI_Reduce的一个区别就是，MPI_Reduce函数将最后的结果只传给了指定的dest_process 号进程，而MPI_Allreduce函数可以将结果传递给所有的进程，因此所有的进程都能接收到结果。MPI_Allreduce函数的原型也因此不需要指定目标进程号：
> int MPI_Reduce(
			void*			input_data_p	/* in */
			void*			output_data_p	/* out */
			int				count			/* in */
			MPI_Datatype	datatype		/* in */
			MPI_Op			operator		/* in */
			int				dest_process	/* in */
			MPI_Comm		comm			/* in */
			);

> int MPI_Reduce(
			void*			input_data_p	/* in */
			void*			output_data_p	/* out */
			int				count			/* in */
			MPI_Datatype	datatype		/* in */
			MPI_Op			operator		/* in */
			MPI_Comm		comm			/* in */
			);
