#pragma once
#include <Windows.h>

class CTimer
{
public:
	CTimer();

	void vStart();
	double dCurrentTime();
	void vStop();

	double dGetTime() { return d_seconds; };

private:
	double d_seconds = 0.0;
	LARGE_INTEGER li_start;
	LARGE_INTEGER li_end;
	LARGE_INTEGER li_frequency;
};