#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
float *gen_rand_list(int32_t size, float bound);
void update_coords(float* xs, float* ys, float* zs, float* vx, float* vy, float* vz, int32_t size);
float sum_array(float* arr,int32_t size);
void time_and_print(float* xs, float* ys, float* zs, float* vx, float* vy, float* vz, int32_t iters, int32_t array_size);