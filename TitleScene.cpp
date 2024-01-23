#include "TitleScene.h"
#include "SceneTransition.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Direct3D.h"

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hStartButton_(-1), hOption_(-1),
	mousePos_(0, 0, 0)
{
}

void TitleScene::Initialize()
{
	hStartButton_ = Image::Load("Assets\\Logo_StartButton.png");
	assert(hStartButton_ >= 0);
	hOption_ = Image::Load("Assets\\Logo_Option.png");
	assert(hOption_ >= 0);
}

void TitleScene::Update()
{
	mousePos_ = Input::GetMousePosition();

	mousePos_.x = mousePos_.x - (Direct3D::scrWidth / 2);
	mousePos_.y = mousePos_.y - (Direct3D::scrHeight / 2);

	XMFLOAT3 SBRightUp = XMFLOAT3(tStartButton_.position_.x + (Direct3D::scrWidth * tStartButton_.scale_.x / 2),
									;
	float SBRightDown = tStartButton_.position_.x - (Direct3D::scrWidth * tStartButton_.scale_.x / 2);
	float SBRightDown = tStartButton_.position_.x - (Direct3D::scrWidth * tStartButton_.scale_.x / 2);
	float SBRightDown = tStartButton_.position_.x - (Direct3D::scrWidth * tStartButton_.scale_.x / 2);

	std::string resStr = std::to_string((float)mousePos_.x) + ", " + std::to_string(mousePos_.y) + "\n";
	OutputDebugString(resStr.c_str());
}

void TitleScene::Draw()
{
	tStartButton_.position_.y = -0.1f;
	tOption_.position_.y = -0.5f;
	tStartButton_.scale_ = XMFLOAT3(0.3f, 0.1f, 1);
	tOption_.scale_ = XMFLOAT3(0.3f, 0.1f, 1);

	Image::SetTransform(hStartButton_, tStartButton_);
	Image::SetTransform(hOption_, tOption_);
	Image::Draw(hStartButton_);
	Image::Draw(hOption_);
}

void TitleScene::Release()
{
}