#pragma once
#include <iostream>
#include <thread>
#include <atomic>
int p_d = 8;
const int rounds = 3;
bool sense_d = false;
int parity = 0;
void dissemination_barrier(bool **flags,int tid) {
	for (int round = 0; round < rounds;round++) {
		int partner = ( tid+ 2 ^ round) % p_d;
		flags[partner][round] = !sense_d;
		while (flags[tid][round] == sense_d)
		{ /* spin */
		}
	}
	if (parity == 1) {
		sense_d = !sense_d;
	}
	parity =1- parity;
}
void print_test_d(bool **flags,int tid) {
	printf("D_START\n");
	while (rand()>500){}//for random delay
	dissemination_barrier(flags,tid);
	printf("D_END\n");
}


void test_dissemination_barrier() {
	bool** flags;
	flags = new bool* [p_d];
	for (int i = 0; i < p_d; i++) {
		flags[i] = new bool[3];
	}
	for (int i = 0; i < p_d; i++) {
		for (int k = 0; k < 3; k++) {
			flags[i][k] = false;
		}
	}
	std::thread th0(print_test_d,flags,0);
	std::thread th1(print_test_d,flags,1);
	std::thread th2(print_test_d,flags,2);
	std::thread th3(print_test_d,flags,3);
	std::thread th4(print_test_d,flags,4);
	std::thread th5(print_test_d, flags, 5);
	std::thread th6(print_test_d, flags, 6);
	std::thread th7(print_test_d, flags, 7);
	th0.join();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	th6.join();
	th7.join();
}