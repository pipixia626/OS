#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{

    int shmid;
    char *shmaddr;
    shmid = 589854;
    shmaddr = (char *)shmat(shmid, NULL, 0);
    if ((int)shmaddr == -1)
    {
        perror("shmat error.\n");
        exit(1);
    }
    printf("%s\n", shmaddr);
    shmdt(shmaddr);

    return 0;
}