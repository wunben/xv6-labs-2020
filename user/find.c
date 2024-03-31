#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void find(char *path, char *targer)
{
    char buf[512], *p;
    int fd;
    struct dirent de; // 一个文件夹结构体题？？？
    struct stat st;

    // path目录描述符
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type)
    {
    // 是文件的情况
    case T_FILE:
        // printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
        p = path + strlen(path)-1;
        while(p>=path && *p!='/') p--;
        // printf("==%s==  targer:%s \n", p+1, targer);
        if(!strcmp(p+1, targer)){
            printf("%s\n", path);
        }
        break;
    // 是目录的情况
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("ls: path too long\n");
            break;
        }
        

        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';  // 将buf 从“path”变为“path/”
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0)
                continue;
            if((!strcmp(de.name, "."))||(!strcmp(de.name, "..")))continue;

            memmove(p, de.name, DIRSIZ);  // 将buf 从“path/”变为“path/xxx”
            p[DIRSIZ] = 0;
            if (stat(buf, &st) < 0)
            {
                printf("ls: cannot stat %s\n", buf);
                continue;
            }
            // printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
            // printf("%s\n", buf);
            find(buf, targer);
        }
        break;
    }
    close(fd);
    
}

void main(int args, char *argv[])
{
    if (args < 2)
    {
        printf("find args error\n");
    }

    find(argv[1], argv[2]);
    exit(0);
}