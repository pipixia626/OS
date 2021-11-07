#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    printf(" I am father ,my pid is %d\n", getpid());
    pid_t pid1 = fork();
    if (pid1 == -1)
    {
        perror("error\n");
    }
    if (pid1 == 0)
    {
        printf("I am the first kid，my pid is %d\n", getpid());
        //execlp("echo", "echo", "executed by execl", NULL);
        exit(0);
    }
    if (pid1 > 0)
    {

        wait(NULL);
        printf("I am also a  father,my pid is %d\n",getpid());

        pid_t pid2 = fork();
        if (pid2 == 0)
        {

            printf("I am the second kid,my pid is %d\n", getpid());
        }
    }
    return 0;
}