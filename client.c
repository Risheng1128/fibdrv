#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"

long long elapse(struct timespec *start, struct timespec *end)
{
    return (long long) (end->tv_sec - start->tv_sec) * 1e9 +
           (long long) (end->tv_nsec - start->tv_nsec);
}

int main()
{
    char buf[256];
    int offset = 100; /* TODO: try test something bigger than the limit */

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    struct timespec start, end;
    for (int i = 0; i < offset; i++) {
        lseek(fd, i, SEEK_SET);
        clock_gettime(CLOCK_MONOTONIC, &start);
        read(fd, buf, 256);
        clock_gettime(CLOCK_MONOTONIC, &end);
        long int ktime = write(fd, buf, 256);
        printf("%lld %ld %lld\n", elapse(&start, &end), ktime,
               elapse(&start, &end) - ktime);
    }

    close(fd);
    return 0;
}
