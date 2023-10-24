#include "SceneManager.h"
#include "../TestScene.h"
#include "../SpriteTest.h"
#include "Model.h"

SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_SPRITE;
	nextSceneID_ = currentSceneID_;
	Instantiate<SpriteTest>(this);
}

void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		Model::Release();
		//後片付け終了

		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
				break;
		case SCENE_ID_SPRITE:
			Instantiate<SpriteTest>(this);
			break;
		}
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
}
