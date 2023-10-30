#include "SceneTransition.h"
#include "MapEditScene.h"
#include "Engine/SceneManager.h"

SceneTransition::SceneTransition(GameObject* parent)
	: GameObject(parent, "SceneTransition")
{
}

void SceneTransition::Initialize()
{
	Instantiate<MapEditScene>(this);
}

void SceneTransition::Update()
{
}

void SceneTransition::Draw()
{
}

void SceneTransition::Release()
{
}