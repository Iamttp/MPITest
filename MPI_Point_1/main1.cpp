#include <iostream>
#include <string.h>
#include <mpi.h>
using namespace std;

const int max_string = 100;

int main ()
{
	int comm_sz=0;
	int my_rank=0;
	char greeting[max_string];
	
	MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);

	 if(my_rank!=0){
		sprintf(greeting,"Greetings from process %d of %d!",my_rank,comm_sz);
		MPI_Send(greeting,strlen(greeting),MPI_CHAR,0,0,MPI_COMM_WORLD);
	}
	else{
		cout<<"Greetings from process "<<my_rank<<" of "<<comm_sz<<"!"<<endl;
		for(int i=1;i<comm_sz;i++){
			/**
			 * 注意可以传入MPI_STATUS_IGNORE忽略接受状态
			 *	int MPI_SOURCE;
    		 * 	int MPI_TAG;
    		 * 	int MPI_ERROR;
			*/
			MPI_Status local_status;
			
			//MPI_Recv(greeting,max_string,MPI_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			//使用 MPI_ANY_SOURCE 来接收，类似的可以使用 MPI_ANY_TAG 发送
			MPI_Recv(greeting,max_string,MPI_CHAR,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&local_status);
			cout<<greeting<<endl;

			cout<< "\nMPI_Recv当前状态--MPI_Status:"
			<< "\nlocal_status.MPI_SOURCE:"<<local_status.MPI_SOURCE 
			<< "\nlocal_status.MPI_TAG:"<<local_status.MPI_TAG 
			<< "\nlocal_status.MPI_ERROR:"<<local_status.MPI_ERROR <<endl<<endl;
		}
	}
	
	MPI_Finalize ();
	return 0;
}
