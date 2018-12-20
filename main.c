#include "common.h"
#include "ex1.h"
#include "ex2.h"
#include "ex3.h"

typedef int (*ex_func)(void);

ex_func ex_func_arr[65] = { NULL,
    ex1, ex2, ex3, NULL, NULL, NULL, NULL, NULL,    /* 1  - 8 */
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* 9  - 16 */
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* 17 - 24 */
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* 25 - 32 */
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* 33 - 40 */
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* 41 - 48 */
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* 49 - 56 */
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* 57 - 60 */
};

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
    if (ex_func_arr[exercise] != NULL) {
        ret = ex_func_arr[exercise]();
    } else {
        ret = -ENOENT;
    }

    if (ret == 0) {
        printf("Success\n");
    } else {
        printf("Error: %s", strerror(-ret));
    }

    return 0;
}
