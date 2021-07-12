#include "CSharedMethod.h"

int CSharedMethod::wrap(int x, int low, int high)
{
	ASSERT(low < high);
	const int n = (x - low) % (high - low);
	return (n >= 0) ? (n + low) : (n + high);
}

double CSharedMethod::clamp(double x, double low, double high)
{
	ASSERT(low <= high && "Å¬’l <= Å‘å’l");
	return min(max(x, low), high);
}

bool CSharedMethod::FrameTimeObsever(int _index)
{
	_time++;
	if (_time % _index == 0) { return true; }
	return false;
}
