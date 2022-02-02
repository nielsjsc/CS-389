#pragma once
#include <stdio.h>

int main()
{
    rand_mean();
    return 0;
}


rand_mean() {
    const int list_length;
    double rand_seed;
    printf("Enter the list length: ");
    scanf("%d", &list_length);//get list length from user
    printf("Enter the random seed: ");
    scanf("%lf", &rand_seed);//get random seed from user
    void srand(rand_seed); //set random seed
    double mean = 0;
    int curr_int;
    for (int i = 0; i < list_length; i++) {
        curr_int = rand() % 100;
        printf("%d \n", curr_int);
        mean += curr_int;
    }
    mean /= list_length;
    printf("MEAN:    %lf", mean);
    return 0;
}
