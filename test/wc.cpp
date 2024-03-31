#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
/*wc进程*/
// g++ -o wc wc.cpp
int main(int nums, char *argv[])
{
    char *buf;
    while (int n = read(0, buf, sizeof(buf)))
    {
        std::cout << "收到" << std::endl;
        char *temp;
        sprintf(temp, "wc out: %s", buf);
        write(1, temp, sizeof(temp));
    }
}