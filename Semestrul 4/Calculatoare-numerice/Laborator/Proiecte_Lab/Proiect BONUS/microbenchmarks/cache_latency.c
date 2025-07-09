#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define STRIDE      64               // bytes per cache line
#define SIZES_COUNT 6
// KB sizes to probe L1 → L3
static const size_t SIZES_KB[SIZES_COUNT] = {4, 32, 256, 1024, 2048, 4096};

// How many times to traverse the entire buffer.
// Too small → per-access noise, too large → overflow arithmetic.
// 1000–10000 is usually fine.
#define REPEATS 5000

// Memory fence to prevent speculative execution
#define MEMORY_FENCE asm volatile("" ::: "memory")

int main() {
    printf("size_kb,latency_ns\n");

    for (int s = 0; s < SIZES_COUNT; s++) {
        size_t kb      = SIZES_KB[s];
        size_t bytes   = kb * 1024;
        size_t entries = bytes / STRIDE;

        // Allocate aligned memory
        volatile char *buf = aligned_alloc(STRIDE, bytes);
        if (!buf) {
            fprintf(stderr, "Error: Memory allocation failed for size %zu KB\n", kb);
            return EXIT_FAILURE;
        }

        // Build pointer-chase list
        for (size_t i = 0; i < entries; i++) {
            size_t next = ((i + 1) % entries) * STRIDE;
            ((size_t *)buf)[i] = next;
        }

        // Memory fence to ensure proper ordering
        MEMORY_FENCE;

        // Time REPEATS full traversals
        struct timespec t0, t1;
        if (clock_gettime(CLOCK_MONOTONIC, &t0) != 0) {
            perror("Error: Failed to get start time");
            free((void *)buf);
            return EXIT_FAILURE;
        }

        for (int r = 0; r < REPEATS; r++) {
            size_t idx = 0;
            for (size_t i = 0; i < entries; i++) {
                idx = ((size_t *)buf)[idx / STRIDE];
            }
        }

        if (clock_gettime(CLOCK_MONOTONIC, &t1) != 0) {
            perror("Error: Failed to get end time");
            free((void *)buf);
            return EXIT_FAILURE;
        }

        uint64_t total_ns = (uint64_t)(t1.tv_sec  - t0.tv_sec) * 1000000000ull
                          + (uint64_t)(t1.tv_nsec - t0.tv_nsec);

        // Calculate average latency per access
        double avg_ns = (double)total_ns / ((double)entries * (double)REPEATS);

        // Print with 3 decimal places (e.g., 5.123 ns)
        printf("%zu,%.3f\n", kb, avg_ns);

        // Free allocated memory
        free((void *)buf);
    }

    return 0;
}