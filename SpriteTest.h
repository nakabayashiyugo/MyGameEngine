#pragma once
#include "Engine/GameObject.h"
class Sprite;

class SpriteTest
	:public GameObject
{
	Sprite *pSprite;
public:
	SpriteTest(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

