#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main() {
    printf("hello\n");
    int dad, child = 0;
    int status;
    __pid_t pid;
    pid = fork();
    printf("hello afterfork\n");
    if(pid <0) {
        perror("fork failed!");
        return 1;
    } else if (pid == 0){   //child's process
        printf("this is child \n");
        child = getpid();
        printf("child (from child):%d \n", child);
        exit(10);
    } else if (pid >0){  //dad's process
        printf("this is dad\n");
        dad = getpid();
        printf("dad (from dad):%d\n", dad);
        printf("child (from dad):%d \n", pid);
        wait(&status); //bury child's process
        if (WIFEXITED(status)) {  //check if child's bury
            int exit_code = WEXITSTATUS(status);
            printf("child exit code: %d", exit_code);
        }
        
    }
    return 0;
}