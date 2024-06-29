#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // since memory is allocated on stack, we can't allocate too much memory; most systems have a
    // stack size limit of ~8 MB (passing in 7 works; passing in 8 causes a segfault on my system)
    if (argc != 2) {
        printf("Usage: %s <memory_to_allocate_mb>\n", argv[0]);
        return 1;
    }
    printf("PID: %d\n", getpid());
    int memory_to_allocate_mb = atoi(argv[1]);
    printf("Allocating %d MB of memory\n", memory_to_allocate_mb);
    // a char is 1 byte, so we allocate memory_to_allocate_mb * 1024 * 1024 bytes
    int num_elements = memory_to_allocate_mb * 1024 * 1024;
    char memory[num_elements]; // allocated on stack, not heap; no need to free()
    printf("Memory allocated: %.2f MB\n", (float)sizeof(memory) / 1024 / 1024);
    while (1) {
        for (int i = 0; i < num_elements; i++) {
            memory[i] = 0;
        }
    }
    return 0;
}
