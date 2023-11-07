#pragma once
#include "Engine/GameObject.h"
#include "StageOrigin.h"

class TestScene
	:public GameObject, StageOrigin
{
public:
	TestScene(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	void Read();

	MATHDEDAIL GetTableMath(int x, int z) { return math_.at(x).at(z); }
};

