#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define MAX_MB    256     // up to 256 MiB
#define STEP_MB   32      // step size

int main() {
    printf("size_mb,time_ns\n");
    for (int mb = STEP_MB; mb <= MAX_MB; mb += STEP_MB) {
        size_t SIZE = (size_t)mb * 1024 * 1024;
        volatile char *buf = aligned_alloc(64, SIZE);

        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        memset((void*)buf, 0xFF, SIZE);
        clock_gettime(CLOCK_MONOTONIC, &t1);

        uint64_t dt_ns = (t1.tv_sec - t0.tv_sec)*1000000000ull
                       + (t1.tv_nsec - t0.tv_nsec);

        printf("%d,%llu\n", mb, (unsigned long long)dt_ns);
        free((void*)buf);
    }
    return 0;
}
