#include <stdio.h>
#include <pthread.h>

void* printID(void * arg){
    pthread_t tid = pthread_self();
    printf("Thread with %lu is running\n", tid);
    return NULL;
}

int main() {
    pthread_t thread_ID;
    pthread_create(&thread_ID, NULL, printID, NULL);
    pthread_t thread_ID1;
    pthread_create(&thread_ID1, NULL, printID, NULL);
    pthread_join(thread_ID,NULL);
    pthread_join(thread_ID1,NULL);
    return 0;
}