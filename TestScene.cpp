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
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
