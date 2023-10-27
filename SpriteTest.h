#pragma once
#include "Engine/GameObject.h"
class Sprite;

class SpriteTest
	:public GameObject
{
	int hPict_;
public:
	SpriteTest(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};

