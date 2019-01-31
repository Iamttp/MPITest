#include <iostream>
#include <mpi.h>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

//我们的walker
typedef struct {
    int location;                   //walker的实际位置
    int num_steps_left_in_walk;     //walker能够for循环步数
} Walker;

//随机漫步--为进程分配合适的域（domain）
void decompose_domain(int domain_size, int world_rank,
                      int world_size, int* subdomain_start,
                      int* subdomain_size) {
    if (world_size > domain_size) {
        // Don't worry about this special case. Assume the domain
        // size is greater than the world size.
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    *subdomain_start = domain_size / world_size * world_rank;
    *subdomain_size = domain_size / world_size;
    if (world_rank == world_size - 1) {
        // Give remainder to last process
        *subdomain_size += domain_size % world_size;
    }
}

void initialize_walkers(int num_walkers_per_proc, int max_walk_size,
                        int subdomain_start, int subdomain_size,
                        vector<Walker>* incoming_walkers) {
    Walker walker;
    for (int i = 0; i < num_walkers_per_proc; i++) {
        // Initialize walkers in the middle of the subdomain
        walker.location = subdomain_start;
        walker.num_steps_left_in_walk =
            (rand() / (float)RAND_MAX) * max_walk_size;
        incoming_walkers->push_back(walker);
    }
}

void walk(Walker* walker, int subdomain_start, int subdomain_size,
          int domain_size, vector<Walker>* outgoing_walkers) {
    while (walker->num_steps_left_in_walk > 0) {
        if (walker->location == subdomain_start + subdomain_size) {
            // Take care of the case when the walker is at the end
            // of the domain by wrapping it around to the beginning
            if (walker->location == domain_size) {
                walker->location = 0;
            }
            outgoing_walkers->push_back(*walker);
            break;
        } else {
            walker->num_steps_left_in_walk--;
            walker->location++;
        }
    }
}

void send_outgoing_walkers(vector<Walker>* outgoing_walkers, 
                           int world_rank, int world_size) {
    // Send the data as an array of MPI_BYTEs to the next process.
    // The last process sends to process zero.
    MPI_Send((void*)outgoing_walkers->data(), 
             outgoing_walkers->size() * sizeof(Walker), MPI_BYTE,
             (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);

    // Clear the outgoing walkers
    outgoing_walkers->clear();
}

void receive_incoming_walkers(vector<Walker>* incoming_walkers,
                              int world_rank, int world_size) {
    MPI_Status status;

    // Receive from the process before you. If you are process zero,
    // receive from the last process
    int incoming_rank =
        (world_rank == 0) ? world_size - 1 : world_rank - 1;
    MPI_Probe(incoming_rank, 0, MPI_COMM_WORLD, &status);

    // Resize your incoming walker buffer based on how much data is
    // being received
    int incoming_walkers_size;
    MPI_Get_count(&status, MPI_BYTE, &incoming_walkers_size);
    incoming_walkers->resize(
        incoming_walkers_size / sizeof(Walker));
    MPI_Recv((void*)incoming_walkers->data(), incoming_walkers_size,
             MPI_BYTE, incoming_rank, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE); 
}


int main ()
{
    int world_size=0;
    int world_rank=0;
    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
  
    srand(time(NULL) * world_rank);

    //domain_size 域大小
    int domain_size = 100;      
    int subdomain_start = 0 , subdomain_size = 0;
    // Find your part of the domain
    decompose_domain(domain_size, world_rank, world_size,
                    &subdomain_start, &subdomain_size);

    vector<Walker> incoming_walkers;
    int num_walkers_per_proc = 20;
    int max_walk_size = 50;
    // Initialize walkers in your subdomain
    initialize_walkers(num_walkers_per_proc, max_walk_size,
                    subdomain_start, subdomain_size,
                    &incoming_walkers);

    cout << "Process " << world_rank << " initiated " << num_walkers_per_proc
        << " walkers in subdomain " << subdomain_start << " - "
        << subdomain_start + subdomain_size - 1 << endl;

    vector<Walker> outgoing_walkers;
    
    // Determine the maximum amount of sends and receives needed to
    // complete all walkers
    // = 50 / (100 / world_size) + 1;
    int maximum_sends_recvs = max_walk_size / (domain_size / world_size) + 1;
    for (int m = 0; m < maximum_sends_recvs; m++) 
    { // Determine walker completion later
        // Process all incoming walkers
        for (int i = 0; i < incoming_walkers.size(); i++) {
            walk(&incoming_walkers[i], subdomain_start, subdomain_size,
                domain_size, &outgoing_walkers); 
        }
        cout << "Process " << world_rank << " sending " << outgoing_walkers.size()
            << " outgoing walkers to process " << (world_rank + 1) % world_size
            << endl;
        // Send all outgoing walkers to the next process.
        send_outgoing_walkers(&outgoing_walkers, world_rank,
                            world_size);

        // Receive all the new incoming walkers
        receive_incoming_walkers(&incoming_walkers, world_rank,
                                world_size);

        cout << "Process " << world_rank << " received " << incoming_walkers.size()
            << " incoming walkers" << endl;
    }
    cout << "Process " << world_rank << " done1" << endl;
    ////////////////////////////////////////
    /////不解！！！，有时候其他进程done1在进程0 rec 接受之前出现，如果是输入输出问题，那么如何调试大程序？？
    // int cou = 0;
    // if (world_rank == 0) {
    //     for(int i = 0; i < world_size-1; i++)
    //     {
    //         MPI_Recv(&cou, 1,
    //             MPI_INT, i+1 , 0, MPI_COMM_WORLD,
    //             MPI_STATUS_IGNORE); 
    //         cout << "rec:\t" <<"i+1:"<< i+1 << "\tcou:"<< cou <<endl;
    //     }
    //     cout << "Walker的最终位置：\n";
    //     for(int i = 0; i < outgoing_walkers.size(); i++)
    //     {
    //         cout << "\""<< i <<"\"  :"<< incoming_walkers[i].location << endl;
    //     }
    // }
    // else
    // {
    //     cou = world_rank;
    //     MPI_Send(&cou, 1, 
    //         MPI_INT, 0, 0, MPI_COMM_WORLD);
    // }
    ////////////////////////////////////////
    cout << "Process " << world_rank << " done2" << endl;
    MPI_Finalize ();
	return 0;
}
