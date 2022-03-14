#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

pthread_mutex_t m;
double result = 0;

void* dex(void* value) {

    double* v = (double*) value;

    pthread_mutex_lock(&m);

    result += v[0] * v[1];

    pthread_mutex_unlock(&m);

    return 0;
}

int main() {

    int n;
    scanf("%d", &n);

    double* vecs = (double*)calloc(n * 2, sizeof(double));

    pthread_t* thid = (pthread_t*)calloc(n, sizeof(pthread_t));
    
    for (int i = 0; i < n * 2; i += 2)
        scanf("%lg", vecs + i);

    for (int i = 1; i < n * 2; i += 2)
        scanf("%lg", vecs + i);

    for (int i = 0; i < n * 2; i += 2) {

        int result = pthread_create(thid + i / 2, NULL, dex, (void*)(&vecs[i]));

        if (result) {

            printf("Some errors with threads!!!\n");
            exit(-1);
        }
    }

    for (int i = 0; i < n; ++i) {
        pthread_join(thid[i], NULL);
    }

    printf("The result is: %8.8lg\n", result);

    return 0;
}
