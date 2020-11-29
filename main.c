#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#define OUTFILE "log.txt"

static void signalhandler(int signo) {
    if(signo == SIGUSR1) {
        printf("\nparent PID: %d\n", getppid());
    }
    if(signo == SIGINT) {
        int fd = open(OUTFILE,O_APPEND | O_CREAT | O_WRONLY, 0644);
        if(fd == -1) {
            printf("error %d: %s", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }

        char msg[] = "exit from SIGINT\n";
        write(fd, msg, sizeof(msg)-1);
        fd = close(fd);
        exit(EXIT_SUCCESS);
    }
}


int main() {
    signal(SIGUSR1, signalhandler);
    signal(SIGINT, signalhandler);

    while(1) {
        printf("PID: %d\n", getpid());
        sleep(1);
    }
    
    return 0;
}
