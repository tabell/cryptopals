#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>

#include "common.h"

// calls stat to get size then allocates mem for entire file
// returns 0 on success, negative errno on failure
int file_read_alloc(
        char *filename,
        char **mem,
        size_t *size)
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
        } else {
            log("error %d reading from %s: %s", errno, filename, strerror(errno));
            free(buf);
            return -errno;
        }
    }

    if (size) {
        *size = ret;
    }
    *mem = buf;
    return 0;
}

int ice_file(
        char *filename)
{
    char *buf;
    size_t bytes;
    int ret = file_read_alloc(filename, &buf, &bytes);
    if (ret) {
        return ret;
    }
    uint8_t out[bytes + 1];
    uint8_t *key = "ICE";

    xor(buf, bytes, key, 3, out, bytes);
    write(fileno(stdout), out, bytes);

    free(buf);
    return 0;
}

