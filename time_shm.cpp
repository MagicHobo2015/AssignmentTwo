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

int main( int argc, char** argv )
{
    // Variables
    char* command = nullptr;
    pid_t childID;
    std::string test = "Hello World!";
    // shared mem stuff
    const int SIZE = 4096;
    const char* NAME = "mem";
    int fd;
    char* ptr = nullptr;
    // /memStuff
    // End Variables

    // Create some shared memory
    fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    // fix the size
    ftruncate(fd, SIZE);
    // map the memObject
    ptr = (char*) mmap(0, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);

    // start a child process
    childID = fork();

    // make sure child is created
    if (childID < 0) {

        // if youre here the child process was not created
        std::cout << "Something went wrong" << std::endl;

    } else if ( childID == 0 ) {
        // In the child process here
        // test the shared memory
        sprintf(ptr, "Hello World!");

    } else {
        // this pid could only be the parent
        // now wait for child to do its thing
        wait(NULL);
        printf("Parent gets: %s\n", ptr);

            // this is for debugging ********************************* TODO: remove
        std::cout << "else block: " << childID << std::endl;
        // ***************************************************** END REMOVE

    }

    // 
    return 0;
}
// this will return just the command.
char* stripCommand(char** argv) { return nullptr; }

// makes shared mem the size of
void* createSharedMem(size_t memSize) 
{
    return NULL;
}