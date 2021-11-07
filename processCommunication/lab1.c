#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#define SVKEY 75
#define REQ 1

typedef struct msgs
{
    long type;
    char text[1024];
} inform;

int msgId;
int pid;
int *text;
struct msgs msg;

void server()
{
    msgId = msgget(SVKEY, IPC_CREAT); //创建消息队列
    msg.type = REQ;
    msgrcv(msgId, &msg, 1024, msg.type, 0); //接收client用户进程标识数消息
    text = (int *)msg.text;                 //获取client进程的正文

    int pid = *text; //获取当前client的pid
    printf("serving for client :pid=%d \n", pid);
    msg.type = pid;   //消息类型为client进程标识数
    *text = getpid(); //获取server的进程标识数
    msgsnd(msgId, &msg, sizeof(int), 0);
    exit(0);
}

void client()
{
    msgId = msgget(SVKEY, IPC_CREAT);
    pid = getpid();
    msg.type = REQ;
    text = (int *)msg.text;
    *text = pid;
    msgsnd(msgId, &msg, sizeof(int), 0);
    msgrcv(msgId, &msg, 1024, pid, 0);
    pid = *text;
    printf("receive reply form :pid=%d \n", pid);
    exit(0);
}

int main()
{
    pid_t pid1 = fork();
    if (pid1 == 0)
        client();
    else
    {
        pid_t pid2 = fork();

        if (pid2 == 0)
            server();
    }
    return 0;
}