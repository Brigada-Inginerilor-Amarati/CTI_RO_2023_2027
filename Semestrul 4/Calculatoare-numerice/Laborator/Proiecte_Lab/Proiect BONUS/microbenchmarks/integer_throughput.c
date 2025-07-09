#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define SIZES_COUNT 4
static const uint64_t ITERS[SIZES_COUNT] = {
    100000000ULL,
    500000000ULL,
    1000000000ULL,
    2000000000ULL
};

int main() {
    printf("ops,time_s\n");
    for (int idx = 0; idx < SIZES_COUNT; idx++) {
        uint64_t ITER = ITERS[idx];
        volatile uint64_t a = 1, b = 2, c = 0;

        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        for (uint64_t i = 0; i < ITER; i++) {
            c += a * b;
            a ^= b;
        }
        clock_gettime(CLOCK_MONOTONIC, &t1);

        double elapsed = (t1.tv_sec - t0.tv_sec)
                       + (t1.tv_nsec - t0.tv_nsec) * 1e-9;
        // two ops per iteration: multiply and xor
        printf("%llu,%.6f\n",
               (unsigned long long)(ITER * 2),
               elapsed);
    }
    return 0;
}
