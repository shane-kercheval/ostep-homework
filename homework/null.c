#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int *p = NULL;
    //segfault
    // printf("p value: %d\n", *p);
    p = malloc(sizeof(int) * 10);
    assert(p != NULL);
    // for (int i = 0; i < 10; i++) {
    //     p[i] = i;
    // }
    free(p);
    // this works, even though p is unitialized and freed
    for (int i = 0; i < 10; i++) {
        printf("i[%d]: %d\n", i, p[i]);
    }
    return 0;
}
