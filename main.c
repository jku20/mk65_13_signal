#include <unistd.h>
#include <stdio.h>
#include <signal.h>

static void signalhandler(int signo) {
    if(signo == SIGUSR1) {
        printf("\nparent PID: %d\n", getppid());
    }
}


int main() {
    signal(SIGUSR1, signalhandler);

    while(1) {
        printf("PID: %d\n", getpid());
        sleep(1);
    }
    
    return 0;
}
