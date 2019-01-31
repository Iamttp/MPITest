EXECS1=mpi_hello.o
EXECS2=mpi2_hello.o
#?= 是如果没有被赋值过就赋予等号后面的值
MPICC?=mpicxx

#make (all)
#make mpi_hello.o 	单独编译
#make mpi2_hello.o  单独编译
#make clean

all: ${EXECS1} ${EXECS2}

mpi_hello.o:main1.cpp
	${MPICC} -o mpi_hello.o main1.cpp

mpi2_hello.o:main2.cpp
	${MPICC} -o mpi2_hello.o main2.cpp

#make clean
clean:
	rm -f ${EXECS1}
	rm -f ${EXECS2}