EXECS=mpi_hello.o
#?= 是如果没有被赋值过就赋予等号后面的值
MPICC?=mpicxx

all: ${EXECS}

mpi_hello.o:main1.cpp
	${MPICC} -o mpi_hello.o main1.cpp

#make clean
clean:
	rm -f ${EXECS}