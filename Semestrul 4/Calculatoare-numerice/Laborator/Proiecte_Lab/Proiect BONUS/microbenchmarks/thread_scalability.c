#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <omp.h>

#define ITER_PER_THREAD 200000000ULL

int main() {
    printf("threads,ops,time_s\n");
    // query max threads
    int maxt = omp_get_max_threads();
    for (int t = 1; t <= maxt; t++) {
        omp_set_num_threads(t);
        volatile uint64_t a = 1, b = 2, c = 0;

        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);

        #pragma omp parallel
        {
            uint64_t local_a = a, local_b = b, local_c = 0;
            #pragma omp for
            for (uint64_t i = 0; i < ITER_PER_THREAD; i++) {
                local_c += local_a * local_b;
                local_a ^= local_b;
            }
            #pragma omp atomic
            c += local_c;
        }

        clock_gettime(CLOCK_MONOTONIC, &t1);
        double elapsed = (t1.tv_sec - t0.tv_sec)
                       + (t1.tv_nsec - t0.tv_nsec) * 1e-9;
        uint64_t total_ops = ITER_PER_THREAD * t * 2; // two ops each
        printf("%d,%llu,%.6f\n", t,
               (unsigned long long)total_ops,
               elapsed);
    }
    return 0;
}
