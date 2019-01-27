# Test	简单测试MPI:	
## 		编译：
#### 		mpicxx -g -Wall -o mpi_hello.o main1.cpp 
#### 		mpicc         是编译C程序的
#### 		mpicxx        是编译C++程序的
#### 		-g            允许使用调试器
#### 		-Wall         显示警告（W大写）
#### 		-o outfile.o  编译出可执行的文件，文件名为outfile.o
#### 		-02           告诉编译器对代码进行优化

## 		运行：
#### 		编译完成后，开始运行，可由-n后面的数字来调节创建进程数。
#### 		mpirun -n 4 ./mpi_hello.o

## 		运行结果：
#### 		Greetings from process 0 of 4!
#### 		Greetings from process 1 of 4!
#### 		Greetings from process 2 of 4!
#### 		Greetings from process 3 of 4!

## 		记录：
#### 		SPMD（单程序多数据流）程序
#### 		分布式内存系统编程
#### 		进程通信

#### 		OMPI_DECLSPEC int MPI_Send(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
#### 		OMPI_DECLSPEC int MPI_Recv(void * buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status * status)
##### 		前三个参数定义了消息的内容，剩下的参数定义了消息的目的地
##### 		dest/source 接受消息的进程号 
##### 		tag 非负int，区分不同的消息
##### 		comm 通信子，指定通信范围 

# MPI2	并行化梯形积分法:
##			/* 串行程序伪代码 */
#### 		/* input a,b,n  n:划分段数*/
#### 		h = (b-a)/n;
####		approx = ( f(a) + f(b) ) / 2.0
####		for(i=1; i<=n-1; i++)
####		{
####			approx += f( a + i*h );
####		}
####		approx = h*approx;

## 		编译：
#### 		mpicxx -g -Wall -o mpi_hello.o main1.cpp 

## 		运行及结果：
#### 		编译完成后，开始运行，可由-n后面的数字来调节创建进程数。
#### 		mpirun -n 4 ./mpi_hello.o

####		With n = 1024 trapezoids, our estimate
####		of the integral from 0.000000 to 3.000000 = 1.148197004588656e+01
