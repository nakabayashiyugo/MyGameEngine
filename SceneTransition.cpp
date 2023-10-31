#include "SceneTransition.h"
#include "MapEditScene.h"
#include "Engine/SceneManager.h"

SceneTransition::SceneTransition(GameObject* parent)
	: GameObject(parent, "SceneTransition"), isFinished_(false), mathSize_{0, 0, 0}, mapEdit_Num_(0)
{
	mathSize_.x = (rand() % 15) + 5;
	mathSize_.y = (rand() % 15) + 5;
}

void SceneTransition::Initialize()
{
	Instantiate<MapEditScene>(this);
}

void SceneTransition::Update()
{
	if (isFinished_)
	{
		Instantiate<MapEditScene>(this);
		mapEdit_Num_ = 1;
		isFinished_ = true;
	}
}

void SceneTransition::Draw()
{
}

void SceneTransition::Release()
{
}