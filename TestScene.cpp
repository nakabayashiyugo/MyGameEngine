#include "TestScene.h"
#include "Stage.h"
#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene"), isCreate_newTable_(false), table_xsize_(15), table_zsize_(15)
{
}

void TestScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Controller>(this);
}

void TestScene::Update()
{
	if (isCreate_newTable_)
	{
		Instantiate<Stage>(this);
		isCreate_newTable_ = false;
	}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}

void TestScene::SetCreateNewTable(bool _isCreate)
{
	isCreate_newTable_ = _isCreate;
}

void TestScene::SetTableSize(int _xsize, int _zsize)
{
	table_xsize_ = _xsize;
	table_zsize_ = _zsize;
}

int TestScene::GetTableXSIZE()
{
	return this->table_xsize_;
}

int TestScene::GetTableZSIZE()
{
	return this->table_zsize_;
}
