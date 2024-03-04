#pragma once
#include<iostream>
#include<chrono>
class timer {
public:
	timer() {
		start = std::chrono::system_clock::now();
	}
	~timer() {
		auto end = std::chrono::system_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
	}
private:
	std::chrono::system_clock::time_point start;
};