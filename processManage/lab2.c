#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf(" i am facther ,my pid is %d \n", getpid());

    pid_t pid1 = fork();

    if (pid1 == 0)
    {

        printf("I am the first  son ,my pid is %d\n", getpid());
        exit(0);
    }

    pid_t pid2 = fork();

    if (pid2 == 0)
    {

        printf("i am  the second  son ,my pid is %d \n", getpid());
        exit(0);
    }

    return 0;
}