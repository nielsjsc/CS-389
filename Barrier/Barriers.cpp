#pragma once
#include <iostream>
#include <thread>
#include <atomic>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "Centralized.h"
#include "MCS.h"
#include "Dissemination.h"

void test_barriers() {
	static std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	std::chrono::duration<double> diff;
	start = std::chrono::high_resolution_clock::now();
	test_centralized_barrier();
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	double ms = diff.count() * 1000.0;
	std::cout << "TIME FOR CENTRALIZED BARRIER" << ms << "ms"<< std::endl;
	start = std::chrono::high_resolution_clock::now();
	test_dissemination_barrier();
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	ms = diff.count() * 1000.0;
	std::cout << "TIME FOR DISSEMINATION BARRIER" << ms << "ms" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	test_MCS_barrier();
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	ms = diff.count() * 1000.0;
	std::cout << "TIME FOR MCS BARRIER" << ms << "ms" << std::endl;

}







int main() {
	test_barriers();

}