#pragma once
/* The purpose of this class is simply to take out some
	of the syntax of the C++11's high resolution clock.
	It's merely here to make it easier to read:
	Here's the usage:
	
	Stopwatch s;  //starts the timer
	....  //some intensive computation
	double seconds = s.recordTime();

	To use it again either make a new stopwatch or call reset().
*/

#include <chrono>
using namespace std;

class Stopwatch {
private:
	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point endTime;

public:
	Stopwatch() {
		reset();
	}

	void reset() {
		startTime = chrono::high_resolution_clock::now();
	}

	double recordTime() {
		endTime = chrono::high_resolution_clock::now();
		return timeElapsed();
	}

	double timeElapsed() {
		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
		return time_span.count();
	}

};	