#include<stdio.h>
#include <sys/stat.h>
int main()
{
    mkfifo("myfifo1" , 0744);
    mknod("mknod1" , S_IFIFO|0744, 0);
    return 0;
}

//strace -c mkfifo
