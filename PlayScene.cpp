#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "SceneTransition.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize_x();
	ZSIZE = (int)pTrans_->GetMathSize_z();
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);
	Math_Resize(XSIZE, ZSIZE, &math_);
	Read();
	
}

void PlayScene::Initialize()
{
	pStage_ = (Stage*)FindObject("Stage");
	pPlayer_ = (Player*)FindObject("Player");
	pStage_->Instantiate<Stage>(this);
	pPlayer_->Instantiate<Player>(this);
}

void PlayScene::Update()
{
	pStage_ = (Stage*)FindObject("Stage");
	pPlayer_ = (Player*)FindObject("Player");
	if (pPlayer_->is_Goal())
	{
		pPlayer_->KillMe();
		pStage_->KillMe();
		KillMe();
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}

void PlayScene::Read()
{
	std::ifstream read;
	read.open("saveMath1", std::ios::in | std::ios::binary);
	//  �t�@�C�����J��
	//  ios::in �͓ǂݍ��ݐ�p  ios::binary �̓o�C�i���`��

	if (!read) {
		std::cout << "�t�@�C�����J���܂���";
		return;
	}
	//  �t�@�C�����J���Ȃ������Ƃ��̑΍�

	//�t�@�C���̍Ō�܂ő�����
	for (int i = 0; i < XSIZE; i++)
	{
		for (int j = 0; j < ZSIZE; j++)
		{
			read.read((char*)&math_[i][j].mathType_, sizeof(math_.at(i).at(j).mathType_));
			//������ł͂Ȃ��f�[�^��ǂ݂���

		}
	}
	read.close();  //�t�@�C�������

	read.open("saveConvRot1", std::ios::in | std::ios::binary);
	//  �t�@�C�����J��
	//  ios::in �͓ǂݍ��ݐ�p  ios::binary �̓o�C�i���`��

	if (!read) {
		std::cout << "�t�@�C�����J���܂���";
		return;
	}
	//  �t�@�C�����J���Ȃ������Ƃ��̑΍�

	//�t�@�C���̍Ō�܂ő�����
	for (int i = 0; i < XSIZE; i++)
	{
		for (int j = 0; j < ZSIZE; j++)
		{
			read.read((char*)&math_[i][j].converyor_rotate_, sizeof(math_.at(i).at(j).converyor_rotate_));
			//������ł͂Ȃ��f�[�^��ǂ݂���

		}
	}
	read.close();  //�t�@�C�������
}