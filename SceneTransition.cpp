#include "SceneTransition.h"
#include "MapEditScene.h"
#include "Engine/SceneManager.h"

SceneTransition::SceneTransition(GameObject* parent)
	: GameObject(parent, "SceneTransition"), isFinished(false), math_xsize_(15), math_ysize(15)
{
}

void SceneTransition::Initialize()
{
	Instantiate<MapEditScene>(this);
}

void SceneTransition::Update()
{
	if (isFinished)
	{
		int a = 0;
	}
}

void SceneTransition::Draw()
{
}

void SceneTransition::Release()
{
}