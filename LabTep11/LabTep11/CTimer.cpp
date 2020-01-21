#include "CTimer.h"

CTimer::CTimer()
{
	QueryPerformanceFrequency(&li_frequency);
}

void CTimer::vStart()
{
	QueryPerformanceCounter(&li_start);
}

double CTimer::dCurrentTime()
{
	QueryPerformanceCounter(&li_end);
	return (li_end.QuadPart - li_start.QuadPart) / li_frequency.QuadPart;
}

void CTimer::vStop()
{
	QueryPerformanceCounter(&li_end);
	d_seconds = (li_end.QuadPart - li_start.QuadPart) / li_frequency.QuadPart;
}