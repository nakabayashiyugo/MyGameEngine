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

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	void SetIsFinished(bool _isFinished) { isFinished_ = _isFinished; };

	XMFLOAT3 GetMathSize() { return mathSize_; };

	int GetMapEditNum() { return mapEdit_Num_; };
};