/*********************************************************************************************
 *               Shared memory object Version                                                 *
 *   Author(s):                                                                               *
 *       Joshua Land, Simon Lariz, Jesus Contreras, Quan Duong                                *
 *                                                                                            *
 *  Description: This version will use a pipe, so that our processes can communicate with     *
 *               each other                                                                   *
 *  See the read me for further information.                                                  *
 *********************************************************************************************/

// includes
#include <stdio.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

// definition of READ_END and WRITE END macros
#define READ_END 0
#define WRITE_END 1

int main(int argc, char **argv)
{
    // pid_t for fork() process id
    pid_t childID;
    // int array for pipe creation
    int fd[2];

    // create pipe (if pipe() == -1 pipe failed)
    if (pipe(fd) == -1)
    {
        printf("Pipe failed\n");
        return -1;
    }

    childID = fork();

    // check if fork was successful
    if (childID < 0)
    {
        // fork failed
        printf("Something went wrong (fork failed)\n");
    }

    // child process
    if (childID == 0)
    {
        // startTime to record start of command execution
        struct timeval startTime;
        // close READ_END of pipe
        close(fd[READ_END]);
        // get startTime
        gettimeofday(&startTime, NULL);
        // write startTime to WRITE_END of pipe
        write(fd[WRITE_END], &startTime, sizeof(startTime));
        // close WRITE_END of pipe
        close(fd[WRITE_END]);
        // execute command
        execvp(argv[1], &argv[1]);
    }
    // parent process
    else
    {
        // readStartTime (time read from pipe), endTime (end time for command), elapsed_time (time subtraction or total time))
        struct timeval readStartTime, endTime, elapsed_time;
        // wait for child process to exit
        wait(NULL);
        // close WRITE_END of pipe
        close(fd[WRITE_END]);
        // read pipe for startTime
        read(fd[READ_END], &readStartTime, sizeof(readStartTime));
        // close READ_END of pipe
        close(fd[READ_END]);
        // get endTime
        gettimeofday(&endTime, NULL);
        // calculate total execution time
        timersub(&endTime, &readStartTime, &elapsed_time);
        // print total elapsed time
        printf("\nElapsed time: %ld.%06ld seconds\n", elapsed_time.tv_sec, elapsed_time.tv_usec);
    }
    return 0;
}