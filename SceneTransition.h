#pragma once
#include "Engine/GameObject.h"

class SceneTransition
	:public GameObject
{
	bool isFinished_;

	int math_xsize_;
	int math_ysize_;
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

