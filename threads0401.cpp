#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXIMUM_THREADS_COUNT 8

pthread_mutex_t mut;

typedef struct Vectors {

    double* vec1;
    double* vec2;

    size_t size;

    int num;

} Vectors;

void VectorsInit(Vectors* vecs, size_t n, int num);

void VectorsDestructor(Vectors* vecs);

void* dex(void* value);

void solvetion(Vectors* vecs, pthread_t* thid, size_t n, size_t m);

int main() {
    
    size_t n;
    scanf("%ld", &n);

    size_t m;
    scanf("%ld", &m);

    Vectors* vecs;

    if (m > MAXIMUM_THREADS_COUNT)
        m = MAXIMUM_THREADS_COUNT;

    if (m > n)
        m = n;

    size_t size = n / m;

    size_t final_step = size + n % m;

    vecs = (Vectors*)calloc(m, sizeof(Vectors));

    for (int i = 0; i < m - 1; ++i)
        VectorsInit(&vecs[i], size, i);

    VectorsInit(&vecs[m - 1], final_step, m - 1);

    pthread_t* thid;
    thid = (pthread_t*)calloc(m, sizeof(pthread_t));

    solvetion(vecs, thid, n, m);
    
    free(thid);

    for (int i = 0; i < m; ++i)
        VectorsDestructor(&vecs[i]);

    free(vecs);
    return 0;
}

void VectorsInit(Vectors* vecs, size_t n, int num) {

    vecs->vec1 = (double*)calloc(n, sizeof(double));
    vecs->vec2 = (double*)calloc(n, sizeof(double));

    vecs->size = n;
    vecs->num  = num;
}

void VectorsDestructor(Vectors* vecs) {
    
    free(vecs->vec1);
    free(vecs->vec2);
}

void solvetion(Vectors* vecs, pthread_t* thid, size_t n, size_t m) {

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < vecs[i].size; ++j)
            scanf("%lg", &vecs[i].vec1[j]);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < vecs[i].size; ++j)
            scanf("%lg", &vecs[i].vec2[j]);

    for (int i = 0; i < m; ++i) {
        
        int err = pthread_create(&thid[i], NULL, dex, (void*)(&vecs[i]));

        if (err) {

            printf("Threads error occured!!!\n");
            exit(-1);
        }
    }

    double result = 0;
    void* results;

    for (int i = 0; i < m; ++i) {

        pthread_join(thid[i], &results);

        result += *(double*)results;

        free(results);
    }
        
    printf("Result of multiplying : %8.8lg\n", result);
}

void* dex(void* value) {

    double* result = (double*)malloc(sizeof(double));
    *result = 0;

    Vectors* vecs = (Vectors*)value;

    printf("thread num: %d\n", vecs->num);

    for (int i = 0; i < vecs->size; ++i)
        *result += vecs->vec1[i] * vecs->vec2[i];

    return (void*)result;
}
