#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    printf("%s\n", argv[0]);

    //创建
    int shmid;
    shmid = shmget(IPC_PRIVATE, 1000, IPC_CREAT | 0600);
    printf("shmid:%d\n", shmid);
    if (shmid < 0)
    {
        perror("shmget error");
        exit(1);
    }
    printf("create shared memory OK. shmid=%d\n", shmid);

    //写数据
    char *shmaddr = (char *)shmat(shmid, NULL, 0);
    if ((int)shmaddr == -1)
    {
        perror("shmat error.\n");
        exit(1);
    }
    strcpy(shmaddr, "hello, world!");
    shmdt(shmaddr);

    return 0;
