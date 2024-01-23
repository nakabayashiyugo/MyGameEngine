#include "Timer.h"
#include "Windows.h"
#include "Engine/Image.h"

Timer::Timer(GameObject* parent):
	GameObject(parent, "Timer"),
	count_time_(0),
	current_time_(0),
	limit_time_(30),
	hFrame_(-1), hGage_(-1), hFrameOutline_(-1),
	hTime_(-1)
{
}

void Timer::Initialize()
{
	hFrame_ = Image::Load("Assets\\Timer_Frame.png");
	assert(hFrame_ >= 0);
	hGage_ = Image::Load("Assets\\Timer_Gage.png");
	assert(hGage_ >= 0);
	hFrameOutline_ = Image::Load("Assets\\Timer_FrameOutline.png");
	assert(hFrameOutline_ >= 0);
	hTime_ = Image::Load("Assets\\choriso-.png");
	assert(hTime_ >= 0);
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
	tFrame_.position_ = XMFLOAT3(-0.6f, 0.8f, 0);
	tFrameOutline_.position_ = XMFLOAT3(-0.6f, 0.8f, 0);
	tGage_.position_ = 
		XMFLOAT3(-(((float)limit_time_ / 100) - (float(limit_time_ - current_time_) / 100)) - 0.6f,
		0.8f, 0);
	tFrame_.scale_ = XMFLOAT3(0.3f, 0.1f, 1);
	tGage_.scale_ = XMFLOAT3(float(limit_time_ - current_time_) / 100, 0.1f, 1);
	tFrameOutline_.scale_ = XMFLOAT3(0.31f, 0.11f, 1);

	Image::SetTransform(hGage_, tGage_);
	Image::SetTransform(hFrame_, tFrame_);
	Image::SetTransform(hFrameOutline_, tFrameOutline_);
	Image::Draw(hGage_);
	Image::Draw(hFrame_);
	Image::Draw(hFrameOutline_);


	tTime_.position_ = XMFLOAT3(-0.4f, 0.8f, 0);
	tTime_.scale_ = XMFLOAT3(0.3f, 0.1f, 1);
	Image::SetTransform(hTime_, tTime_);
	Image::Draw(hTime_);
}

void Timer::Release()
{
}