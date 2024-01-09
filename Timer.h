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

	//初期化
	void Initialize();

	//更新
	bool Time_Update();

	//開放
	void Release();

	void Time_Reset() { count_time_ = 0; }
};