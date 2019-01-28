#include "mpi.h"  
#include <stdio.h>  
#include <cmath>

double Trap(double left_endpt, double right_endpt, double trap_count, double base_len);
double f(double x);
bool get_input(int my_rank,int comm_sz,double* a,double* b,int* n);

int main(int argc, char* argv[])
{
    int my_rank = 0, comm_sz = 0, n = 1024, local_n = 0;
    double a = 0.0, b = 3.0, h = 0, local_a = 0, local_b = 0;
    double local_double = 0, total_int = 0;
    int source;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    get_input(my_rank,comm_sz,&a,&b,&n);

    h = (b - a) / n;       /*  h is the same for all processes  */
    local_n = n / comm_sz; /*  So is the number of trapezoids */

    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;
    local_double = Trap(local_a, local_b, local_n, h);

    //集合通信，MPI_SUM求和
    //total_int只用在进程0上，但所有进程都要传递一个实际参数
    MPI_Reduce(&local_double, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        printf("With n = %d trapezoids, our estimate\n", n);
        printf("of the integral from %f to %f = %.15e\n", a, b, total_int);
        
    }
    MPI_Finalize();
    return 0;
}

//子区域的积分函数
double Trap(double left_endpt, double right_endpt, double trap_count, double base_len)
{
    double estimate = 0, x = 0;
    int i;

    estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
    for (i = 1; i <= trap_count - 1; i++)
    {
        x = left_endpt + base_len;
        estimate += f(x);
    }
    estimate = estimate*base_len;
    return estimate;
}
//数学函数
double f(double x)
{
    return pow(x, 3);
}
//获取输入，0进程从键盘读取，非0进程从0进程获取
bool get_input(int my_rank,int comm_sz,double* a,double* b,int* n)
{
    if(my_rank==0){	//用户输入
		printf(" enter a,b,n \n");
		scanf("%lf %lf %d",a,b,n);
    }
    //数据广播
    MPI_Bcast(a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    return true;
}

