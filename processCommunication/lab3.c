#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// int shmget(key_t key, int size, int shmflg)，开辟或使用一块共享内存。
// void *shmat(int shmid, const void *shmaddr, int shmflg)， 将参数shmid所指向的共享内存与当前进程连接。当使用某共享内存时，需要先使用shmat，达成连接。
// int shmdt(const void *shmaddr)，将先前用shmat连接的共享内存与当前进程解除连接。参数shmaddr为shmat返回的共享内存的地址。
// int shmctl(int shmid, int cmd, struct shmid_ds *buf)，控制内存的操作。当cmd为IPC_RMID时，删除shmid所指的共享内存。
//单个进程对共享内存操作

// 1、创建一块共享内存，获取它的id。
// 2、根据获取的id和当前进程的内存地址建立映射关系；写入字符串“hello，word！”；断开映射关系。
// 3、重新建立映射关系，读取数据并打印。
// 4、删除共享内存。
int main()
{
    //创建
    int shmid;
    shmid = shmget(IPC_CREAT, 1000, IPC_CREAT | 0600);
    if (shmid < 0)
    {
        perror("shaget error\n");
        exit(1);
    }
    printf("create shared memory OK. shmid=%d\n", shmid);
    //写数据
    char *shmaddr = (char *)shmat(shmid, NULL, 0);
    if ((int)shmaddr == -1)
    {
        perror("shmat error\n");
        exit(1);
    }
    strcpy(shmaddr, "hello, world!");
    shmdt(shmaddr);
    //读数据
    shmaddr = (char *)shmat(shmid, NULL, 0);
    if ((int)shmaddr == -1)
    {
        perror("shmat error.\n");
        exit(1);
    }
    printf("%s\n", shmaddr);
    shmdt(shmaddr);

    //删除
    shmctl(shmid, IPC_RMID, NULL);
}