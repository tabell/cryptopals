#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>

#include "common.h"

int file_read_alloc(
        char *filename,
        unsigned char **mem)
{
    int fd = -1;
    if (0 > (fd = open(filename, 0))) {
        log("error %d opening %s: %s", errno, filename, strerror(errno));
        return -errno;
    }

    struct stat statbuf = {0};
    if (0 != fstat(fd, &statbuf)) {
        log("error %d stating %s: %s", errno, filename, strerror(errno));
        return -errno;
    }

    char *buf = malloc(statbuf.st_size);
    if (!buf) {
        errno = ENOMEM;
        log("error %d allocating %lu bytes: %s", errno, statbuf.st_size, strerror(errno));
        return -errno;
    }

    int ret;
    if (statbuf.st_size > (ret = read(fd, buf, statbuf.st_size))) {
        if (ret > 0) {
            log("only read %d bytes", ret);
            return -EIO;
        } else {
            log("error %d reading from %s: %s", errno, filename, strerror(errno));
            return -errno;
        }
    }

    *mem = buf;
    return 0;
}

