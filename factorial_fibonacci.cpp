#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int fibonacci(int n) {

    int result = 1;
    int fib1   = 1;
    int fib2   = 1;

    for (int i = 2; i < n; ++i) {
        fib1 = fib2;
        fib2 = result;
        result = fib1 + fib2;
    }

    return result;
}


static int factorial(int n) {
    int result = 1;

    for (int i = 2; i <= n; ++i)
        result *= i;

    return result;
}

int main(void) {
    
    int n;
    scanf("%d", &n);

    pid_t cpid = 0;

    switch (cpid = fork()) {

        case -1:
            printf("fork() error occured!\n");
            break;

        case 0:
            printf("This is a child process :)\n");
            printf("I count %d fibonacci number\n", n);
            printf("It is %d\n", fibonacci(n));
            break;
        
        default:
            printf("This is a parent process $)\n");
            printf("I will count a factorial from %d\n", n);
            printf("It is %d\n", factorial(n));

    }

    return 0;
}
