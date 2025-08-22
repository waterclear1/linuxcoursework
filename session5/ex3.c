#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define NUM_SIG 5
#define SIGNAL SIGUSR1

volatile sig_atomic_t sigusr1_count = 0;

void handle_sigusr1(int signal){
    printf("Caught signal %d (%s) \n", signal, strsignal(signal));
    sigusr1_count++;
    if (sigusr1_count >=NUM_SIG) exit(0);
}

int main(){
    printf("hello before fork\n");
    int status = 0;
    pid_t pid = 0;  
    pid = fork();
    if(pid == 0 ){   //child
        while (1){
            signal(SIGNAL, handle_sigusr1);
        }
        
    } else if(pid > 0) {  //dad
        sleep(2); //ensure child is already established
        for (int i = 0; i < NUM_SIG; i++){
            kill(pid, SIGNAL);
            sleep(1);   
        }
        wait(&status);
        printf("\nChild terminated.\n");  //bury child's process
        if (WIFEXITED(status)) {  //check if child's buried
            int exit_code = WEXITSTATUS(status);
            printf("child exit code: %d \n ", exit_code);
        }




    }

    return 0;
}