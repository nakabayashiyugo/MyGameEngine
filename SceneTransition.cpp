#include "SceneTransition.h"
#include "MapEditScene.h"
#include "Engine/SceneManager.h"
#include "TestScene.h"

SceneTransition::SceneTransition(GameObject* parent)
	: GameObject(parent, "SceneTransition"), mathSize_{0, 0, 0}, sceneState_(SCENE_MAPEDIT1)
{
	mathSize_.x = (rand() % 15) + 5;
	mathSize_.y = (rand() % 15) + 5;
}

void SceneTransition::Initialize()
{
	
}

void SceneTransition::Update()
{
	switch (sceneState_)
	{
	case SCENE_MAPEDIT1:Instantiate<MapEditScene>(this);break;
	case SCENE_MAPEDIT2:Instantiate<MapEditScene>(this); break;
	case SCENE_STAGE:Instantiate<TestScene>(this); break;
	default:
		break;
	}

}

void SceneTransition::Draw()
{
}

void SceneTransition::Release()
{
}