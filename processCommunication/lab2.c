#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#define key 123
#define SIZE 1024

main()
{
    int shmid;
    char *shmaddr;
    int shmid2;
    char *shmaddr2;

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        //父进程写东西
        shmid = shmget(key, SIZE, IPC_CREAT);
        struct shmid_ds shmbuf;
        shmaddr = (char *)shmat(shmid, NULL, 0);
        printf("the share memory :%s\n", shmaddr);
        const char *chmstr = "pid1 do something\n";
        sprintf(shmaddr, chmstr); //向共享内存写入信息
        shmctl(shmid, IPC_STAT, &shmbuf);
        shmdt(shmaddr); //断开共享内存
    }
    else
    {
        pid_t pid2 = fork();
        if (pid2 == 0)
        {

            shmid2 = shmget(key, SIZE, IPC_CREAT);
            shmaddr2 = (char *)shmat(shmid2, NULL, 0);
            const char *chmstr2 = "pid2 do something\n";
            sprintf(shmaddr2, chmstr2);     //向共享内存写入信息
            shmdt(shmaddr2);                //断开共享内存
            shmctl(shmid2, IPC_RMID, NULL); //销毁}
        }
    }
}