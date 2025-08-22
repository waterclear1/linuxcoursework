#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_SIG 10

volatile sig_atomic_t sigalrm_count = 0;

void handle_sigalrm(int signal){
    printf("Recieved %d (%s)\n",signal, strsignal(signal));
    sigalrm_count++;
    if (sigalrm_count >=NUM_SIG) exit(0);
}


int main(){
    printf("The program started\n");
    signal(SIGALRM, handle_sigalrm);
    while (1) {
        alarm(1);
        printf("sigalrm_count +1\n");
        pause();
    }
    
    return 0;
}