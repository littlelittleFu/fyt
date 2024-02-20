#pragma once
#include<iostream>
#include<chrono>
class STimer
{
public:
	STimer() {
		auto tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
		auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
		m_StartTime = tmp.count();
	};
	~STimer() {
		auto tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
		auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
		std::cout << "cur life cycle cast:" << tmp.count() - m_StartTime << " ms!" << std::endl;
	};


private:
	int64_t m_StartTime = 0;
};