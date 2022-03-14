#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

pthread_mutex_t mutex;
int a = 0;

void* mythread1(void* value) {

    pthread_t mythid;
    mythid = pthread_self();

    pthread_mutex_lock(&mutex);

    a += 1;

    printf("Thread and result1: %ld %d\n", mythid, a);

    pthread_mutex_unlock(&mutex);

    return 0;
}

void* mythread2(void* value) {

    pthread_t mythid;
    mythid = pthread_self();

    pthread_mutex_lock(&mutex);

    a += 3;

    printf("Thread and result2: %ld %d\n", mythid, a);

    pthread_mutex_unlock(&mutex);

    return 0;
}

int main(void) {

    pthread_t thid1, thid2;
    int result;
    
    pthread_mutex_init(&mutex, NULL);

    result = pthread_create(&thid1, NULL, mythread1, NULL);

    if (result) {

        printf("Error on thread creation!!!\n");
        exit(-1);
    }

    result = pthread_create(&thid2, NULL, mythread2, NULL);

    if (result) {

        printf("Error on thread creation!!!\n");
        exit(-1);
    }

    /* mythid = pthread_self(); */

    pthread_mutex_lock(&mutex);

    a += 1;

    pthread_mutex_unlock(&mutex);

    /* printf("Thread created: %ld\n", thid); */
    /* printf("Thread and result2: %ld %d\n", mythid, a); */

    pthread_join(thid1, NULL);
    pthread_join(thid2, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
