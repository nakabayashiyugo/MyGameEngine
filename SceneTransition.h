#pragma once
#include "Engine/GameObject.h"

class SceneTransition
	:public GameObject
{
	bool isCreate_newTable_;

	int table_xsize_;
	int table_zsize_;
public:
	SceneTransition(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};

