#pragma once
#include "Engine/GameObject.h"
class Sprite;

class SpriteTest
	:public GameObject
{
	Sprite *pSprite;
public:
	SpriteTest(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

