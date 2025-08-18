#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_READERS 5
#define NUM_WRITERS 2

int shared_resource = 0;  
pthread_rwlock_t rw_lock; 

void* reader_function(void* arg) {
    long id = (long)arg; //distinguish threads

    pthread_rwlock_rdlock(&rw_lock);                

    printf("Student with %ld is reading, the value is %d\n", id, shared_resource);  

    sleep(1);       //simulate the reading time, all students will read in 1 second parallel

    printf("Student with %ld done reading.\n", id);     

    pthread_rwlock_unlock(&rw_lock);

    return NULL;    
}

void* writer_function(void* arg) {
    long id = (long)arg;  //distinguish threads

    printf("Teacher with id %ld is waiting for the student finishing reading\n", id);
    pthread_rwlock_wrlock(&rw_lock);


    printf("Teacher with id %ld is writing new value, old value is %d\n", id, shared_resource);
    
    shared_resource++;
    sleep(1); //simulate writing time

    printf("Teacher with id %ld wrote new value: %d\n", id, shared_resource);  

    pthread_rwlock_unlock(&rw_lock);

    return NULL;
}


int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    pthread_rwlock_init(&rw_lock, NULL);


    for (long i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader_function, (void*)i);
    }

    for (long i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer_function, (void*)i);
    }


    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rw_lock);

    return 0;
}
