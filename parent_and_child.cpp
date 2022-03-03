#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {

    printf("Parent id: %d\n", getpid());
    printf("Process id: %d\n", getppid());

    return 0;
}
