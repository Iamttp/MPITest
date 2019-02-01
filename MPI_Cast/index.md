# 四、MPI_Cast--集合通信：
### 备注：
* assert宏指令是用来诊断程序是否有误的，函数原型如下:
  void assert(int expression)
  宏定义#define NDEBUG 取消assert的诊断。
* 同步：MPI_Barrier(MPI_COMM_WORLD);
* 该程序用于比较MPI_Bcast和my_bcast的速度
  用到了函数MPI_Wtime();

>

广播（broadcast）的主要用途之一是**把用户输入传递给一个分布式程序，或者把一些配置参数传递给所有的进程。**
广播的通信模式看起来像这样：
```cpp
MPI_Bcast(
    void* data,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm communicator)

//MPI_Bcast可能的简单实现
//实际实现使用了一个类似的树形广播算法
void my_bcast(void* data, int count, MPI_Datatype datatype, int root,
              MPI_Comm communicator) {
  int world_rank;
  MPI_Comm_rank(communicator, &world_rank);
  int world_size;
  MPI_Comm_size(communicator, &world_size);

  if (world_rank == root) {
    // If we are the root process, send our data to everyone
    int i;
    for (i = 0; i < world_size; i++) {
      if (i != world_rank) {
        MPI_Send(data, count, datatype, i, 0, communicator);
      }
    }
  } else {
    // If we are a receiver process, receive the data from the root
    MPI_Recv(data, count, datatype, root, 0, communicator,
             MPI_STATUS_IGNORE);
  }
}

```

#### 输出结果：
mpirun -n 4 ./mpi_hello.o 
Data size = 16000, Trials = 100000
Avg my_bcast time = 0.000010
Avg MPI_Bcast time = 0.000009
