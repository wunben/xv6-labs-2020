struct sysinfo {
  uint64 freemem;   // amount of free memory (bytes) 为空闲内存的字节数
  uint64 nproc;     // number of process   设置为state字段不为UNUSED的进程数
};
