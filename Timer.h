#pragma once

#include <chrono>

class Timer {
public:
	Timer() :
		m_beg(clock_::now()) {
	}
	void reset() {
		m_beg = clock_::now();
	}

	double elapsed() const {
		return (clock_::now() - m_beg).count() / 1000000.f;
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	std::chrono::time_point<clock_> m_beg;
};