#include <sys/vfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv)
{
        if (argc != 2) {
                printf("Missing Path\n");
                exit(1);
        }
        int statfsResult;
        struct statfs *statfsBuf;
        statfsBuf = malloc(sizeof(struct statfs));
        statfsResult = statfs(argv[1], statfsBuf);
        if (statfsResult != 0) {
                printf("statfs failed!\n");
                switch(errno) {
                        case EACCES:
                                printf("access denied!\n");
                                break;
                        case EBADF:
                                printf("no valid fd\n");
                                break;
                        case EFAULT:
                                printf("buf or valid invalid address\n");
                                break;
                        case EIO:
                                printf("I/O error!\n");
                                break;
                        case ELOOP:
                                printf("loop!\n");
                                break;
                        default:
                                printf("something else:-P\n");
                                break;
                }
                exit(1);
        }
        long int totalSpace, freeSpace, usedSpace;
        totalSpace = (long int)(statfsBuf->f_blocks) * (long int)(statfsBuf->f_bsize) / 1024;
        freeSpace = (long int)(statfsBuf->f_bfree) * (long int)(statfsBuf->f_bsize) / 1024;
        usedSpace = totalSpace - freeSpace;
        printf("%20s%20s%20s\n", "totalSpace", "usedSpace", "freeSpace");
        printf("%20i%20i%20i\n", totalSpace, usedSpace, freeSpace);
}


