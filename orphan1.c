#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // fork() failed
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process (Zombie) created. PID: %d\n", getpid());
        exit(0); // Child exits immediately
    } else {
        // Parent process
        printf("Parent process (not waiting). PID: %d\n", getpid());
        sleep(10); // Wait to keep parent running without calling wait()
        printf("Parent process finishing without waiting on child.\n");
    }

    return 0;
}