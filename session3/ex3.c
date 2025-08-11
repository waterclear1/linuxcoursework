#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
    pid_t pid;
    int status;
    pid = fork();
    if(pid <0) {
        perror("fork failed!\n");
        return 1;
    } else if (pid == 0) { //child
        int child = getpid();
        printf("child hello, child's pid: %d\n", child);
        exit(0);
    }else {  //dad
        int dad = getpid();
        printf("dad hello, dad's pid: %d\n", dad);
        sleep(30);
        return 0;
    }
}