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

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetIsFinished(bool _isFinished) { isFinished_ = _isFinished; };

