#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

size_t n;
int max_time;

size_t result_size;
size_t actual_size;

// Shared variable
int summator = 0;

pthread_mutex_t pmut;
pthread_cond_t  pcond;

typedef struct array {

    int* nums;

    size_t size;
    size_t capacity;

} array;

void array_init(array* arr);

void array_destructor(array* arr);

void array_realloc(array* arr);

static void read_array(array* arr);

static void print_array(array* arr);

int run_threads(array* arr);


void* producer_routine(void* value);

void* consumer_routine(void* value);

int main() {

    scanf("%ld", &n);

    scanf("%d", &max_time);

    array arr;
    array_init(&arr);

    read_array(&arr);

    result_size = arr.size;
    actual_size = 0;

    print_array(&arr);

    run_threads(&arr);

    array_destructor(&arr);
    return 0;
}

void* producer_routine(void* value) {

    array* arr = (array*)value;

    for (int i = 0; i < arr->size; ++i) {

        pthread_mutex_lock(&pmut);

        summator = arr->nums[i];

        pthread_mutex_unlock(&pmut);
        
        pthread_cond_signal(&pcond);
    }

    printf("1\n");
    summator = 0;
    pthread_cond_broadcast(&pcond);

    return NULL;
}

void* consumer_routine(void* value) {

    int* result;
    result = (int*)malloc(sizeof(int));

    *result = 0;

    pthread_mutex_lock(&pmut);

    printf("2\n");
        
    while (actual_size + 1 < result_size) {

        pthread_cond_wait(&pcond, &pmut);

        *result += summator;

        ++actual_size;
    }

    pthread_mutex_unlock(&pmut);

    return (void*)result;
}

int run_threads(array* arr) {

    pthread_mutex_init(&pmut, NULL);
    pthread_cond_init(&pcond, NULL);

    pthread_t producer;
    if (pthread_create(&producer, NULL, producer_routine, (void*)arr))
        perror("Producer thread error!!!\n");

    pthread_t* consumers;
    consumers = (pthread_t*)calloc(n, sizeof(pthread_t));

    for (int i = 0; i < n; ++i) {

        if (pthread_create(&consumers[i], NULL, consumer_routine, NULL))
            perror("Consumer thread error!!!\n");
    }

    int result = 0;
    void* results;

    pthread_join(producer, NULL);

    for (int i = 0; i < n; ++i) {
        pthread_join(consumers[i], &results);

        result += *(int*)results;

        free(results);
    }
    
    free(consumers);

    pthread_mutex_destroy(&pmut);
    pthread_cond_destroy(&pcond);

    printf("Result of summator is: %d\n", result);
    return 0;
}


void array_init(array* arr) {

    arr->capacity = 2;
    arr->size = 0;

    arr->nums = (int*)calloc(2, sizeof(int));
}

void array_destructor(array* arr) {

    free(arr->nums);
}

void array_realloc(array* arr) {

    if (arr->size == arr->capacity) {

        arr->capacity *= 2;
        arr->nums = (int*)realloc(arr->nums, arr->capacity);
    }
}

static void read_array(array* arr) {

    int temp;

    while (scanf("%d", &temp) == 1) {
        arr->nums[arr->size] = temp;
        ++arr->size;

        array_realloc(arr);
    }
}

static void print_array(array* arr) {

    printf("Size : %ld  Capacity : %ld\n", arr->size, arr->capacity);

    for (int i = 0; i < arr->size; ++i)
        printf("%d ", arr->nums[i]);

    printf("\n");
}
