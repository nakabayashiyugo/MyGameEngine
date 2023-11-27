#include "Timer.h"
#include "Windows.h"

Timer::Timer()
{
	count_time_ = 0;
	current_time_ = 0;
	limit_time_ = 0;
}

Timer::Timer( int _lim_time)
{
	count_time_ = 0;
	current_time_ = 0;
	limit_time_ = _lim_time;
}

void Timer::Initialize()
{
}

bool Timer::Time_Update()
{
	if (limit_time_ - current_time_ == 0)
	{
		return true;
	}
	count_time_++;
	current_time_ = count_time_ / FPS;

	if (count_time_ % FPS == 0)
	{
		std::string resStr = std::to_string(limit_time_ - current_time_) + '\n';
		OutputDebugString(resStr.c_str());
	}
	return false;
}

void Timer::Release()
{
}