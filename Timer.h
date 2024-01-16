#include <string>
#include "Engine/GameObject.h"

const int FPS = 60;

class Timer :public GameObject
{
	int hFrame_, hGage_, hFrameOutline_;
	int hTime_;

	Transform tFrame_, tGage_, tFrameOutline_;
	Transform tTime_;

	int count_time_;
	int current_time_;
	int limit_time_;
public:
	Timer(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update()override;

	void Draw()override;

	//開放
	void Release()override;

	void Time_Reset() 
	{
		count_time_ = 0;
		current_time_ = 0;
	}
	
	bool GetTimeUpped()
	{
		if (current_time_ == limit_time_)
		{
			return true;
		}
		return false;
	}
};