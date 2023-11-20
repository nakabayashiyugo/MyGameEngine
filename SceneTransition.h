#pragma once
#include "Engine/GameObject.h"
#include "StageOrigin.h"

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
	:public GameObject, StageOrigin
{
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

	int GetMathSize_x() { return XSIZE; };
	int GetMathSize_z() { return ZSIZE; };

	int GetSceneState() { return (int)sceneState_; };
	void SetSceneState(int _sceneState) { sceneState_ = (SCENESTATE)_sceneState; };

	void Write();
};
