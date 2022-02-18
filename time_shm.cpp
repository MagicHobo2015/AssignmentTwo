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
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

// end includes

// ProtoTypes
char* stripCommand(char** argv);
// End Proto

int main( int argc, char** argv )
{
    // Variables
    char* command = nullptr;
    pid_t childID;
    // End Variables

    // first start a child process
    childID = fork();

    // make sure child is created
    if (childID < 0) {

        // if youre here the child process was not created
        std::cout << "Something went wrong" << std::endl;

    } else if ( childID == 0 ) {
        // In the child process here

            // this is for debugging ********************************* TODO: remove
        std::cout << "the child proc: " << childID << std::endl;
        // ***************************************************** END REMOVE

    } else {
        // this pid could only be the parent

            // this is for debugging ********************************* TODO: remove
        std::cout << "else block: " << childID << std::endl;
        // ***************************************************** END REMOVE

    }

    // 
    return 0;
}
// this will return just the command.
char* stripCommand(char** argv) { return nullptr; }