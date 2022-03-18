#pragma once
#include <chrono>
#include <iostream>
#include <stddef.h>
double no_read_loop_time(size_t size, size_t reads, size_t stride) {
    size_t sum = 0;
    size_t idx = 0;
    static std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> diff;
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < reads; i++) {
        idx += stride;
        if (idx > size) idx = 0;
    }
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    return diff.count() * 1000.0;
}

void sumRam(size_t size, size_t reads, size_t stride) {
    char* p = (char*)malloc(size);
    size_t sum = 0;
    size_t idx = 0;
    static std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> diff;
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < reads; i++) {
        sum += p[idx];
        idx += stride;
        if (idx > size) idx = 0;
    }
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    double ms = diff.count() * 1000.0;
    double base_ms = no_read_loop_time(size, reads, stride);
    ms -= base_ms;
    ms /= reads;
    std::cout  << size << "                         " << ms << "                 " << (unsigned)sum << std::endl;

    free(p);
}


int main(void) {
    printf("BUFFER SIZE (BYTES)       TIME PER READ(MS)      SUM (FOR TRICKING COMPILER)\n");
    for (size_t s = 4096; s < 100000000; s *= 2)
        sumRam(s, 1000000000, 128);
}
