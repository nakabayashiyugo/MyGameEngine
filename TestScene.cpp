#include "TestScene.h"
#include "Stage.h"
#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene"), isCreate_newTable_(false)
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
