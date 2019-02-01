# 五、MPI_Scatter和MPI_Gather的使用，求平均数：
```cpp
//这个机制对很多平行算法很有用，比如并行的排序和搜索。
MPI_Scatter(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)
//这个机制对很多平行算法很有用，比如并行的排序和搜索。
MPI_Gather(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)
```

### 运行结果：
```
mpirun -n 4 ./mpi_hello.o

Avg of all elements is 0.500057
Avg computed across original data is 0.500047
avg_time:       0.030193
```
