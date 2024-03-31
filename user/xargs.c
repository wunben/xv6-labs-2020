#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"


void main(int args, char* argv[]){
    if(args<3) {
        printf("args error\n");
        exit(0);
    }
    
    char buf[512];
    read(0, buf, 512);
    char* message[MAXARG];  // 记录所有参数
    int temp=1;  // 记录参数个数
    message[0] = buf;
    for(int i=0;i<512;i++){
        if(buf[i]=='\n')
        {
            buf[i] = 0;
            if(buf[i+1]==0) break;
            message[temp++] = &buf[i+1];
        }
    }

    while(temp--){
        int pid = fork();
        if(pid==0){
            char* argv_t[MAXARG];
            argv_t[0] = argv[1];  // grep
            argv_t[1] = argv[2];  //  "hell0"
            argv_t[2] = message[temp];   // 文件名
            exec(argv[1], argv_t);
        }
        wait((int *) 0);
    }
    exit(0);
}