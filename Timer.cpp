#include "Timer.h"
#include "Windows.h"
#include "Engine/Image.h"

Timer::Timer(GameObject* parent):
	count_time_(0),
	current_time_(0),
	limit_time_(30),
	hFrame_(-1), hGage_(-1)
{
}

void Timer::Initialize()
{
	hFrame_ = Image::Load("Assets\\Timer_Frame.png");
	assert(hFrame_ >= 0);
	hGage_ = Image::Load("Assets\\Timer_Gage.png");
	assert(hGage_ >= 0);
}

void Timer::Update()
{
	count_time_++;
	current_time_ = count_time_ / FPS;

	if (count_time_ % FPS == 0)
	{
		std::string resStr = std::to_string(limit_time_ - current_time_) + '\n';
		OutputDebugString(resStr.c_str());
	}
}

void Timer::Draw()
{
	tFrame_.position_ = XMFLOAT3(-0.7f, 0.8f, 0);
	tGage_.position_ = XMFLOAT3(-0.7f, 0.8f, 0);
	tFrame_.scale_ = XMFLOAT3(0.3f, 0.1f, 1);
	tGage_.scale_ = XMFLOAT3(float(limit_time_ - current_time_) / 100, 0.1f, 1);

	Image::SetTransform(hFrame_, tFrame_);
	Image::SetTransform(hGage_, tGage_);
	Image::Draw(hFrame_);
	Image::Draw(hGage_);
}

void Timer::Release()
{
}