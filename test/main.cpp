/***************************************************************************/
/*
第一章 操作系统接口

// 1.1 进程和内存
// g++ -o main mian.cpp
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
    // fork()在父进程中返回子进程的PID
    // 在子进程中返回0
    int pid = fork();

    if (pid > 0) // 父进程
    {
        printf("parent: child=%d\n", pid);
        pid = wait((int *)0); // 告诉操作系统在等待子进程退出时不需要返回任何状态信息。
        printf("child %d is done\n", pid);
    }
    else if (pid == 0) // 子进程
    {
        char *argv[3];
        argv[0] = "echo";
        argv[1] = "hello";
        argv[2] = 0;
        execv("/bin/echo", argv);
        printf("exec error\n");

        printf("child: exiting\n");
        exit(0); // 系统调用导致调用进程停止执行并释放资源 通常0表示成功，1表示失败
    }
    else
    {
        printf("fork error\n");
    }
}
*/

/***************************************************************************/
/**/
// 1.2 I/O和文件描述符
// g++ -o main main.cpp
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd1 = open("out.txt", O_RDWR);
    // int fd2 = open("out.txt", O_RDWR);
    int fd2 = dup(fd1);

    char buf1[] = "hello";
    char buf2[] = "word";
    write(fd1, buf1, sizeof(buf1));
    write(fd2, buf2, sizeof(buf2));
    close(fd1);
    close(fd2);
}

/***************************************************************************/
/*
// 1.3 管道
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
int main()
{
    int p[2]; // 储存管道描述符
    pipe(p);  // 创建管道
    char *argv[]{"wc", 0};
    // 子进程
    if (fork() == 0)
    {
        close(0);                // 关闭标准输入
        dup(p[0]);               // 将管道读改到标准输入上
        close(p[1]);             // 关闭多余管道
        if (execv("wc", argv)) // 启动新进程
            std::cout << "子进程启动失败" << std::endl;
        std::cout << "子进程退出" << std::endl;
    }
    else
    {
        // 父进程
        char buf[512];
        close(1);
        dup(p[1]);
        while (int n = read(0, buf, sizeof(buf)))
        {
            write(1, buf, n);
        }
        wait((int *)0);
        std::cout << "父进程退出" << std::endl;
    }
    exit(0);
}
*/
/***************************************************************************/
