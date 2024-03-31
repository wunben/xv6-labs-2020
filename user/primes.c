#include "kernel/types.h"
#include "user/user.h"

void sonpros(int n, int fd1[2], int fd2[2])
{
    int flage = 0;  // 转发节点标志位
    int p;   // 用于接收转换后的信息
    close(fd1[1]);  // 关闭左边管道的写端
    close(fd2[0]);  // 关闭右边管道的读端
    while (1)
    {
        char buf[1];  // 储存左边进程转发的消息
        char massge;  // 向右边进程发送的消息
        int res_read;
        
        // 从右边管道读取数据
        res_read = read(fd1[0], buf, sizeof(buf)); 
        // printf("son%d read %d byte: %s \n", n, res_read, buf);

        // 数据处理
        p = atoi(buf); // 左边发的数据

        // 如果不是素数改变为转发节点
        if (n % p == 0) flage = 1;

        // 如果read返回值为0，证明左管道不再读写，变为最左边进程
        if (res_read == 0)
        {
            // 不是素数
            if(flage==0)
            {
                printf("prime %d\n", n);
            }
            massge = '0' + n;  


            write(fd2[1], &massge, sizeof(massge));  
            close(fd1[0]);
            close(fd2[1]);
            // printf("son %d\n end", n);
            exit(0);
        }

        // 转发信息
        massge = '0' + p;
        write(fd2[1], &massge, sizeof(massge)); // 转发
    }
}

int main()
{
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    int maxN = 35;

    for (int i = 2; i <= maxN; i++)
    {
        pipe(fd2);  // 创建右管道
        if (fork() == 0)  // 创建子进程
        {
            // 逻辑实现
            sonpros(i, fd1, fd2);  
        }

        // 子进程间通信 创建必须要关闭
        close(fd1[0]);  
        close(fd1[1]);

        // 迭代下一个子进程的左管道就是这个子进程的右管道
        fd1[0] = fd2[0];
        fd1[1] = fd2[1];
    }
    close(fd1[0]);
    close(fd1[1]);
    for (int i = 2; i <= maxN; i++)
        wait((int *)0);
    exit(0);
}