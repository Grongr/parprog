#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

pthread_mutex_t m;

void* func(void* value) {

    pthread_mutex_lock(&m);

    int* v = (int*)value;

    *v = *v + 1;

    pthread_mutex_unlock(&m);

    return 0;

}

int main() {

    pthread_t thid;
    int result;

    int* value;
    *value = 2;


    pthread_mutex_init(&m, NULL);

    result = pthread_create(&thid, NULL, func, (void*)value);

    if (result) {

        printf("Pthread error occured!!!\n");
        exit(-1);
    }

    pthread_join(thid, NULL);

    printf("Value in the end: %d\n", *value);
    return 0;
}
