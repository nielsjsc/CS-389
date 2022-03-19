#pragma once
#include <iostream>
#include <thread>
#include <atomic>
int p = 8;
bool sense_m= false;

void MCS_barrier(bool** flags_m,int tid) {
	int round;
	for (round = 0; // wait for children (depth == first 1)
		((p | tid) & (1 << round)) == 0; round++) {
		while (flags_m[tid][round] != sense_m) { /* spin */ }
	}
	if (round < 3) { // signal + wait for parent (all but root)
		int parent = tid & ~((1 << (round + 1)) - 1);
		flags_m[parent][round] = sense_m;
		while (flags_m[tid][round] != sense_m) { /* spin */ }
	}
	while (round-- > 0) { // wake children
		int child = tid | (1 << round);
		flags_m[child][round] = sense_m;
	}
	sense_m = !sense_m;
}

void print_test_m(bool** flags, int tid) {
	printf("D_START\n");
	while (rand() > 500) {}//for random delay
	MCS_barrier(flags, tid);
	printf("D_END\n");
}




void test_MCS_barrier() {
	bool** flags;
	flags = new bool* [p];
	for (int i = 0; i < p; i++) {
		flags[i] = new bool[3];
	}
	for (int i = 0; i < p; i++) {
		for (int k = 0; k < 3; k++) {
			flags[i][k] = false;
		}
	}
	std::thread th0(print_test_m, flags, 0);
	std::thread th1(print_test_m, flags, 1);
	std::thread th2(print_test_m, flags, 2);
	std::thread th3(print_test_m, flags, 3);
	std::thread th4(print_test_m, flags, 4);
	std::thread th5(print_test_m, flags, 5);
	std::thread th6(print_test_m, flags, 6);
	std::thread th7(print_test_m, flags, 7);
	th0.join();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	th6.join();
	th7.join();
}