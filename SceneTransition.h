#pragma once
#include "Engine/GameObject.h"

enum SCENESTATE
{
	SCENE_MAPEDIT1 = 0,
	SCENE_DELAY1,
	SCENE_MAPEDIT2,
	SCENE_DELAY2,
	SCENE_STAGE,
	SCENE_DELAY3,
};

class SceneTransition
	:public GameObject
{
	XMFLOAT3 mathSize_;

	SCENESTATE sceneState_;

public:
	SceneTransition(GameObject* parent);

	//èâä˙âª
	void Initialize() override;

	//çXêV
	void Update() override;

	//ï`âÊ
	void Draw() override;

	//äJï˙
	void Release() override;

	XMFLOAT3 GetMathSize() { return mathSize_; };

	int GetSceneState() { return (int)sceneState_; };
	void SetSceneState(int _sceneState) { sceneState_ = (SCENESTATE)_sceneState; };
};
