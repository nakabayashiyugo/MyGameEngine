#include <string>
#include "Engine/GameObject.h"

const int FPS = 60;

class Timer :public GameObject
{
	int hFrame_, hGage_;

	Transform tFrame_, tGage_;

	int count_time_;
	int current_time_;
	int limit_time_;
public:
	Timer(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update()override;

	void Draw()override;

	//ŠJ•ú
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