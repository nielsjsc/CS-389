#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>



float *gen_rand_list(int32_t array_size, float bound) {
    float *new_array = malloc(sizeof(float)*array_size); //allocate enough memory for new array

    bool neg_flip;//makes the random number negative or positive to be in range -bound->bound

    float rand_float;//

    while (array_size>0) {
        rand_float = (float)rand() / (float)(RAND_MAX / bound); //get the new rand float in between 0 and bound
        neg_flip = rand() % 2;        //

        if (neg_flip){                //
            rand_float = -rand_float; //turn the float negative randomly
        }

        new_array[array_size-1] = rand_float; //put the rand float in the array
        array_size--;



    }
    return new_array;
    
}
void update_coords(float* xs, float* ys, float* zs, float* vx, float* vy, float* vz, int32_t size) {
    for (int32_t i = 0; i < size; i++) {//update coordinates
        xs[i] = xs[i] + vx[i];
        ys[i] = ys[i] + vy[i];
        zs[i] = zs[i] + vz[i];
    }

}
float sum_array(float* arr, int32_t size) {
    float sum = 0;//set the sum to 0
    for (int i = 0; i < size; i++) {
        sum += arr[i];//sum the array
    }
    return sum;
}
void time_and_print(float* xs, float* ys, float* zs, float* vx, float* vy, float* vz, int32_t iters, int32_t array_size){
   
    clock_t begin = clock();//start clock

    for (int32_t i=0; i < iters; i++) {
        update_coords(xs, ys, zs, vx, vy, vz, array_size);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; //calculate total time taken

    printf("Mean time per coordinate: ");
    printf("%lf",(time_spent/(iters*array_size)));
    printf("us");
    return;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("\n Required arguments: vector_length(N) and iterations_num(M) ");
        return 0;
    }

    char* a = argv[1];//take arguments
    char* b = argv[2];

    int32_t size = atoi(a);//convert arguments to ints
    int32_t iters = atoi(b);

    srand(size); //set random seed

    //setting bound variables so they are floats rather than doubles
    float bound_1 = 1000;
    float bound_2 = 1;
    //create new arrays
    float* xs = gen_rand_list(size, bound_1);
    float* ys = gen_rand_list(size, bound_1);
    float* zs = gen_rand_list(size, bound_1);
    float* vx = gen_rand_list(size, bound_2);
    float* vy = gen_rand_list(size, bound_2);
    float* vz = gen_rand_list(size, bound_2);

    //time and print the results
    time_and_print(xs, ys, zs, vx, vy, vz, iters, size);
    //check the sum
    float chksum = sum_array(xs,size) + sum_array(ys,size) + sum_array(zs,size);
    printf("\n Final checksum is: %f", (chksum));
    //free the memory
    free(xs);
    free(ys);
    free(zs);
    free(vx);
    free(vy);
    free(vz);
    return 0;
}