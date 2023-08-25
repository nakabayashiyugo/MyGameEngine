#pragma once
#include "Engine/GameObject.h"

//�v���C�V�[�����Ǘ�����N���X
class PlayerChild
	: public GameObject
{
	int hModel_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayerChild(GameObject* parent);

	//�f�X�g���N�^
	~PlayerChild();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void OnCollision(GameObject* pTarget) override;
};