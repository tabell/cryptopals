#include "common.h"
#include "ex1.h"

int main(int argc, char *argv[])
{
    printf("Cryptopals solutions\nAlex Bell\nMay 2018\n");
    int exercise = 1;
    int arg;
    int ret = 0;
    if (argc > 1) {
        arg = strtoul(argv[1], NULL, 10);
        if ((arg > 0) && (arg < 100)) {
            exercise = arg;
        }
    }
    printf("Running exercise %d\n", exercise);
    switch (exercise) {
        case 1:
            ret = ex1();
            break;
        default:
            ret = -ENOENT;
            break;
    }

    if (ret == 0) {
        printf("Success\n");
    } else {
        printf("Error: %s", strerror(-ret));
    }

    return 0;
}
