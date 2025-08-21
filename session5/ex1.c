#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>



volatile sig_atomic_t sigint_count = 0;

void handle_signint(int signal){
    printf("Caught signal %d (%s) \n", signal, strsignal(signal));
    sigint_count++;
    if (sigint_count >=3) exit(0);
}




int main (){
    
    printf("Send any signal thrice,....\n");
    signal(SIGINT,handle_signint);

    while(1){
        printf("waiting for signals\n");
        sleep(1);
    }

    return 0;
}