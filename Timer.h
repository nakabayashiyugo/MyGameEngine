#include <string>

const int FPS = 60;

class Timer
{
	int count_time_;
	int current_time_;
	int limit_time_;
public:
	Timer();

	Timer(int _lim_time);

	//‰Šú‰»
	void Initialize();

	//XV
	bool Time_Update();

	//ŠJ•ú
	void Release();

	void Time_Reset() 
	{
		count_time_ = 0;
		current_time_ = 0;
	}
};