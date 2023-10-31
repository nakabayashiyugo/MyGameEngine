#pragma once
#include "Engine/GameObject.h"

class SceneTransition
	:public GameObject
{
	bool isFinished_;

	XMFLOAT3 mathSize_;

	int mapEdit_Num_;
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

	void SetIsFinished(bool _isFinished) { isFinished_ = _isFinished; };

	XMFLOAT3 GetMathSize() { return mathSize_; };

	int GetMapEditNum() { return mapEdit_Num_; };
};