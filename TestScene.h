#pragma once
#include "Engine/GameObject.h"

class TestScene
	:public GameObject
{
	bool isCreate_newTable_;

	int table_xsize_;
	int table_zsize_;
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

	void SetCreateNewTable(bool _isCreate);

	void SetTableSize(int _xsize, int _zsize);

	int GetTableXSIZE();
	int GetTableZSIZE();
};

