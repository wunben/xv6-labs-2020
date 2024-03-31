#include "kernel/types.h"
#include "user/user.h"

int pingpong()
{
    int fd_f2s[2]; // 父进程向子进程发送数据的管道
    int fd_s2f[2]; // 子进程向父进程发送数据的管道

    pipe(fd_f2s);
    pipe(fd_s2f);

    // 子进程
    if (fork() == 0)
    {
        int procpid = getpid(); // 获取当前进程pid
        // 处理父亲进程向子进程发送数据
        // close(fd_f2s[1]); // 关闭 父->子 子进程端写描述符
        // close(fd_s2f[0]);
        
        char buf;
        char data = 'a';
        if (1 == read(fd_f2s[0], &buf, sizeof(buf)))
        printf("%d: received ping\n", procpid);
        write(fd_s2f[1], &data, sizeof(data));
        
    }
    // 父进程
    else
    {
        int procpid = getpid(); // 获取当前进程pid
        
        // close(fd_f2s[0]);       // 关闭 父->子 父进程端读描述符
        // close(fd_s2f[1]);       // 关闭 子->父 父进程端写描述符

        char data = 'a';
        write(fd_f2s[1], &data, sizeof(data));
        char buf;
        if (1 == read(fd_s2f[0], &buf, sizeof(buf)))
        printf("%d: received pong\n", procpid);
        wait((int*)0);
    }
    exit(0);
}