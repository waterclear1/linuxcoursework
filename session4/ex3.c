#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORK 10 
#define READY 1
#define NOT_READY 0

// Shared synchronization primitives
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


// Shared state variables

int data;
int data_ready = NOT_READY;



void* producer_thread(void *arg){
    for (int i = 0; i < MAX_WORK; ++i) {

        pthread_mutex_lock(&lock);
        while (data_ready == READY) {
            // Wait until the consumer has consumed the previous product
            pthread_cond_wait(&cond, &lock);
        }
        data = rand() % 100;
        data_ready = READY; 
        printf("Producer has new product: %d\n", data);
        pthread_cond_signal(&cond); //wake consumer whenever a new product is made 
        pthread_mutex_unlock(&lock);
        
    }
    return NULL;

}
void* consumer_thread(void *arg){
    for (int i = 0; i < MAX_WORK; i++){
        pthread_mutex_lock(&lock);
        while(data_ready == NOT_READY){
            
            printf("Consumer: product is not ready, waiting\n");
            pthread_cond_wait(&cond, &lock);
        }
        printf("consumer: recieved product, go back to sleep\n");
        data_ready = NOT_READY;
        pthread_cond_signal(&cond); // signal producer that consumer is ready for next product
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    pthread_t producer, consumer;
    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer,NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    
    return 0;
}