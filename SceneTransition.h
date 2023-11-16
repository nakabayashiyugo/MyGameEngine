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

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	int GetMathSize_x() { return XSIZE; };
	int GetMathSize_z() { return ZSIZE; };

	int GetSceneState() { return (int)sceneState_; };
	void SetSceneState(int _sceneState) { sceneState_ = (SCENESTATE)_sceneState; };

	void Write();
};
