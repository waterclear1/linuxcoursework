#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    int status;
    int child,dad;
    pid = fork();
    if(pid <0) {
        perror("fork failed!\n");
        return 1;
    } else if (pid == 0) { //child
        child = getpid();
        printf("child hello, child's pid: %d dad's pid:%d \n", child, getppid());
        sleep(5);
        printf("child hello, child's pid: %d new dad's pid:%d \n", child, getppid());
    }else {  //dad
        dad = getpid();
        printf("dad hello, dad's pid: %d\n", dad);
        exit(0);
    }

}