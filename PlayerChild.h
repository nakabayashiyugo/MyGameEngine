#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Fbx;

//�v���C�V�[�����Ǘ�����N���X
class PlayerChild
	: public GameObject
{
	Fbx* pFbx;
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
};