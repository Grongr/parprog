#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXIMUM_THREADS_COUNT 8

pthread_mutex_t mut;

typedef struct Vectors {

    double result;

    double* vec1;
    double* vec2;

    size_t n;

    size_t step;

    size_t step_id;

} Vectors;

void VectorsInit(Vectors* vec, size_t n, size_t m) {

    vec->result  = 0;
    vec->step_id = 0;
    vec->n       = n;

    vec->vec1 = (double*)calloc(n, sizeof(double));
    vec->vec2 = (double*)calloc(n, sizeof(double));

    vec->step = n / m;
}

void VectorsDestructor(Vectors* vec) {

    free(vec->vec1);
    free(vec->vec2);
}

void* dex(void* value) {

    Vectors* v = (Vectors*) value;

    pthread_mutex_lock(&mut);

    size_t i;
    for (i = v->step_id * v->step; i < (v->step_id + 1) * v->step; ++i)
        v->result += v->vec1[i] * v->vec2[i];

    if (i + v->step > v->n)
        for (; i < v->n; ++i)
            v->result += v->vec1[i] * v->vec2[i];
    printf("Step: %ld    Result: %lg\n", v->step_id, v->result);

    ++v->step_id;

    pthread_mutex_unlock(&mut);

    return 0;
}

void solvetion(Vectors* vecs, pthread_t* thid, size_t m) {

    for (int i = 0; i < vecs->n; ++i)
        scanf("%lg", &vecs->vec1[i]);

    for (int i = 0; i < vecs->n; ++i)
        scanf("%lg", &vecs->vec2[i]);

    for (int i = 0; i < m; ++i) {

        /* dex( (void*)vecs ); */

        int err = pthread_create(&thid[i], NULL, dex, (void*)vecs);

        if (err) {

            printf("Thread creation error occured!!!\n");
            exit(-1);
        }
    }

    for (int i = 0; i < m; ++i)
        pthread_join(thid[i], NULL);
}

int main() {

    size_t n;
    scanf("%ld", &n);

    size_t m;
    scanf("%ld", &m);

    if (m > MAXIMUM_THREADS_COUNT)
        m = MAXIMUM_THREADS_COUNT;

    if (m > n)
        m = n;

    Vectors vecs;

    VectorsInit(&vecs, n, m);

    pthread_mutex_init(&mut, NULL);

    pthread_t* thid = (pthread_t*)calloc(m, sizeof(pthread_t));

    solvetion(&vecs, thid, m);

    printf("The result of multiplying is: %8.8lg\n", vecs.result);
    
    VectorsDestructor(&vecs);
    return 0;
}
