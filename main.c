#include <stdbool.h>

#include "common.h"
#include "ex.h"
#include "ex5.h"

typedef int (*ex_func)(void);

ex_func ex_func_arr[65] = { NULL,
    ex1, ex2, ex3, ex4, ex5, ex6, NULL, NULL,    /* 1  - 8 */
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
    fprintf(stderr, "Cryptopals solutions\nAlex Bell\nDecember 2018\n");
    int exercise = 1;
    bool all = true;
    int arg;
    int ret = 0;
    if (argc > 1) {
        arg = strtoul(argv[1], NULL, 10);
        if ((arg > 0) && (arg < 100)) {
            exercise = arg;
            all = false;
        }
    }

    int start, stop;
    if (all) {
        start=1;
        stop=64;
    } else {
        start = exercise;
        stop = exercise;
    }

    for (exercise=start; exercise <= stop; exercise++) {

        if (ex_func_arr[exercise] != NULL) {
            fprintf(stderr, "Running exercise %d\n", exercise);
            ret = ex_func_arr[exercise]();
            if (ret == 0) {
                fprintf(stderr, "Success\n");
            } else {
                fprintf(stderr, "Error: %s", strerror(-ret));
            }
        } else {
            ret = -ENOENT;
        }
    }


    return 0;
}
