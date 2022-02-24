/*********************************************************************************************
 *               Shared memory object Version                                                 *
 *   Author(s):                                                                               *
 *       Joshua Land, Simon Lariz, Jesus Contreras, Quan Duong                                *
 *                                                                                            *
 *  Description: This version will use a shared memory object, so that our processes can      *
 *                   comminucate with each other                                              *
 *  See the read me for further information.                                                  *
 *********************************************************************************************/

/*
2a) The first version, time_shm.c, will have the child process write the starting time to a region of shared 
memory before it calls execvp(). After the child process terminates, the parent will read the starting 
time from shared memory. The region of shared memory should be established before the child process 
is forked, allowing both the parent and child processes access to the region of shared memory.

*/

// our includes
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

// end includes

// ProtoTypes
char* stripCommand(char** argv);
void* createSharedMem(size_t memSize);
// End Proto
static time_t* startTime = NULL;

int main( int argc, char** argv )
{
    // Variables
    char* command = nullptr;
    pid_t childID;
    time_t t = NULL;
    time_t endTime = NULL;
    time_t totalTime = NULL;
    std::string test = "Hello World!";
    // shared mem stuff
    const int SIZE = 4096;
    const char* NAME = "mem";
    int fd;
    // /memStuff
    // End Variables

    // Create some shared memory
    fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    // fix the size
    ftruncate(fd, SIZE);
    // map the memObject
    startTime = (time_t*)mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    // start a child process
    childID = fork();

    // make sure child is created
    if (childID < 0) {

        // if youre here the child process was not created
        std::cout << "Something went wrong" << std::endl;

    } else if ( childID == 0 ) {
        // In the child process here
        // timestamp
        *startTime = time(NULL);
        sleep(.5);
        std::cout << *startTime << std::endl;
        // test the shared memory


    } else {
        // this pid could only be the parent
        // now wait for child to do its thing
        wait(NULL);
        // grab endtime
        endTime = time(NULL);
        // get the shared mem
        t = *startTime;
        // unmap the mem
        munmap(startTime, sizeof SIZE);
        // end - begin is the time it took in ms?.
        totalTime = endTime - t;
        // this just prints whats in the shared mem
        std::cout << totalTime << std::endl;
    }
    return 0;
}
// this will return just the command.
char* stripCommand(char** argv) { return nullptr; }

// makes shared mem the size of
void* createSharedMem(size_t memSize) 
{
    return NULL;
}