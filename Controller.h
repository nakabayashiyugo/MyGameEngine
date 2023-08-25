#pragma once
#include "Engine/GameObject.h"

class Controller
	:public GameObject
{
	XMVECTOR velocity_;
public:
	Controller(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};

