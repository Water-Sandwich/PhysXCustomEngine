#pragma once

#include <chrono>

struct StopWatch {
	std::chrono::time_point<std::chrono::system_clock> _start, _end;
	float msElapsed{};

	inline void start() {
		_start = std::chrono::system_clock::now();
	}

	//returns the amount of time in ms that has elapsed
	inline float stop() {
		_end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = _end - _start;
		msElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
		return msElapsed;
	}

	//does not reset start time
	inline float peek() {
		std::chrono::duration<double> diff = std::chrono::system_clock::now() - _start;
		msElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
		return msElapsed;
	}
};