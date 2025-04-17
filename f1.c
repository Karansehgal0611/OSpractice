#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
        pid_t pid;
        pid = fork();
        if (pid <0)
        {
                fprintf(stderr, "Fork failed");
                return 1;
        }
        else if (pid == 0)
        {
                printf("THis is the child process. PID: %d\n" , getpid());
                printf("Child's parent PID: %d\n", getppid());
        }
        else
        {
                printf("This is the parent process. PID:%d\n", getpid());
                printf("Parent created a child process with PID: %d\n",pid);
        }

return 0;

}
