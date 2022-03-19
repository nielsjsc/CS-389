#pragma once
#include <iostream>
#include <thread>
#include <atomic>
std::atomic<long> counter{ 1 };
bool sense_c = false;


void centralized_barrier(int num_threads) {
	bool local_sense = !sense_c;
	if ((counter.fetch_add(1, std::memory_order_relaxed)) == num_threads) {
		counter = 1;
		sense_c = local_sense;
	}
	else {
		while (sense_c != local_sense) { /* spin */ }
	}

}

void print_test(){//test to show when thread enters and exits barrier
	printf("START\n");
	while (rand() > 500) {}//for random delay
	centralized_barrier(5);
	printf("END\n");
	}
	

void test_centralized_barrier() {
	std::thread th0(print_test);
	std::thread th1(print_test);
	std::thread th2(print_test);
	std::thread th3(print_test);
	std::thread th4(print_test);
	th0.join();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
}
