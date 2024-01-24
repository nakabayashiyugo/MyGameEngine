#pragma once
#include "Engine/GameObject.h"

class TitleScene
	:public GameObject
{
	int hStartButton_, hOption_, hStaful_;

	Transform tStartButton_, tOption_, tStaful_;
	XMFLOAT3 mousePos_;
public:
	TitleScene(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};