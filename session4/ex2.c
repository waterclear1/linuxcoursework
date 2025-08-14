#include <stdio.h>
#include <pthread.h>
#define MAX 1000000
long long counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void *increment(void *arg){
    
    while(1){ //infinite loop, stop condition is placed inside
        pthread_mutex_lock(&lock);
        if(counter == MAX){
            pthread_mutex_unlock(&lock);
            break;
        }
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return  NULL;
    
}

int main() {
    pthread_t thread, thread1 , thread2;

    pthread_create(&thread, NULL, increment, NULL);
    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);
    
    pthread_join(thread, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&lock);
    printf("counter : %lld\n", counter);
    return 0;
}