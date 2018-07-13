#include <stdio.h>
#include <unistd.h>

int main() {
    int f = (int)fork();

    if(f == 0) {
        execl("./ejercicio1a", (char*)NULL);
    } else {
        printf("%d\n", (int)getpid());
        execl("./ejercicio1a", (char*)NULL);
    }
    return(0);
}