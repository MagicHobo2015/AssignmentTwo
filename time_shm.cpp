/*********************************************************************************************
 *               Shared memory object Version                                                 *
 *   Author(s):                                                                               *
 *       Joshua Land, Simon Lariz, Jesus Contreras, Quan Duong                                *
 *                                                                                            *
 *  Description: This version will use a shared memory object, so that our processes can      *
 *                   comminucate with each other                                              *
 *  See the read me for further information.                                                  *
 *********************************************************************************************/
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

// One Global variable for shared mem
static clock_t* workingTime = NULL;

int main( int argc, char** argv )
{   
    // Variables
    pid_t childID;
    clock_t t = NULL;
    const int SIZE = 4096;
    const char* NAME = "mem";
    int fd;
    // End Variables

    // Create some shared memory
    fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    // fix the size
    ftruncate(fd, SIZE);
    // map the memObject
    workingTime = (clock_t*)mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    // start a child process
    childID = fork();

    // make sure child is created
    if (childID < 0) {

        // if youre here the child process was not created
        std::cout << "Something went wrong" << std::endl;

    } else if ( childID == 0 ) {
        // child process here

        // timestamp
        *(workingTime) = clock();

        // run the command
        execvp(argv[1], argv);

    } else {
        // parent
        // now wait for child to do its thing
        wait(NULL);
        // get the shared mem
        t = *workingTime;
        // This gives the number of clock ticks elapsed.
        t = clock() - t;
        // unmap the mem
        munmap(workingTime, sizeof SIZE);

        // formats the ticks to time
        std::cout << "\n" << "Elapsed time:\t" << ((float)t)/CLOCKS_PER_SEC << " seconds" << std::endl;
    }
    return 0;
}
