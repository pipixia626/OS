#include <unistd.h>
#include <stdio.h>
// b c, will print in unordered seq
int main()
{
    printf(" a \n");
    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        printf(" b \n");
        return 0;
    }
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        printf(" c \n");
        return 0;
    }
    return 0;
}
