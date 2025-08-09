#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main (){
    printf("before \n");
    setenv("MY_COMMAND", "ls", 1);  //avoid race condition 
    int status;
    pid_t pid;
    pid = fork();

    if (pid < 0){
        perror("fork failed \n");
        return 1;
    } else if (pid == 0){ // child
        char *string = getenv("MY_COMMAND");
        printf("%s \n", string); 
        if(string != NULL){
            execlp("ls", "ls", NULL);
            perror("execlp failed!");//only when execlp didnt run

        } else {
            perror("cannot find env variable");
            exit (1); 
        }
        
    } else { //dad
        wait(&status);
        if (WIFEXITED(status)) {  //check if child's bury
            int exit_code = WEXITSTATUS(status);
            printf("child exit code: %d \n ", exit_code);
        }
    }

}