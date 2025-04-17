#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        printf("Parent process (PID: %d) terminating, child (PID: %d)\n", getpid(), pid);
        exit(0);
    } else if (pid == 0) {
        sleep(2);
        printf("Child process (PID: %d) started, parent (PID: %d)\n", getpid(), getppid());
        sleep(2);
        printf("Child process (PID: %d) ending, parent (PID: %d)\n", getpid(), getppid());
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}

