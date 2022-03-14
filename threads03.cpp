#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

pthread_mutex_t m;

void* func(void* value) {

    int* v = (int*) value;

    pthread_mutex_lock(&m);

    int result = v[0] + v[1];

    printf("This is %ld thread\n", pthread_self());
    printf("Sum is %d\n", result);
    
    pthread_mutex_unlock(&m);

    return 0;
}

int main() {

    int n;
    scanf("%d", &n);

    int* arr;
    arr = (int*)calloc(n, sizeof(int));

    pthread_t* thid;
    thid = (pthread_t*)calloc(n - 1, sizeof(pthread_t));

    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);

    pthread_mutex_init(&m, NULL);

    for (int i = 0; i < n - 1; ++i) {

        int result = pthread_create(thid + i, NULL, func, (void*)(arr + i));

        if (result) {

            printf("Thread error occured!!!\n");
            exit(-1);
        }
    }

    for (int i = 0; i < n - 1; ++i)
        pthread_join(thid[i], NULL);

    return 0;
}
