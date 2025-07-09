#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define STRIDE      64      // bytes
#define MAX_MB      32      // up to 32 MiB
#define STEP_MB     4       // step size

int main() {
    printf("size_mb,time_ns\n");
    for (int mb = STEP_MB; mb <= MAX_MB; mb += STEP_MB) {
        size_t SIZE = (size_t)mb * 1024 * 1024;
        size_t ITER = SIZE / STRIDE;
        volatile char *buf = aligned_alloc(64, SIZE);

        // build pointer-chasing array
        for (size_t i = 0; i < ITER; i++) {
            size_t next = ((i+1) % ITER) * STRIDE;
            ((size_t*)buf)[i] = next;
        }

        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);

        size_t idx = 0;
        for (size_t i = 0; i < ITER; i++) {
            idx = ((size_t*)buf)[idx / STRIDE];
        }

        clock_gettime(CLOCK_MONOTONIC, &t1);
        uint64_t dt_ns = (t1.tv_sec - t0.tv_sec)*1000000000ull
                       + (t1.tv_nsec - t0.tv_nsec);

        printf("%d,%llu\n", mb, (unsigned long long)dt_ns);
        free((void*)buf);
    }
    return 0;
}
