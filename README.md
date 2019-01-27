Test:	
	编译
	mpicxx -g -Wall -o mpi_hello.o main1.cpp 

	mpicc         是编译C程序的
	mpicxx        是编译C++程序的
	-g            允许使用调试器
	-Wall         显示警告（W大写）
	-o outfile.o  编译出可执行的文件，文件名为outfile.o
	-02           告诉编译器对代码进行优化

	编译完成后，开始运行，可由-n后面的数字来调节创建进程数。
	mpirun -n 4 ./mpi_hello.o

