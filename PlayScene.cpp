#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "SceneTransition.h"
#include "Timer.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), table_Change_(false), player_Num_(0), save_Num_(2)
{
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	XSIZE = (int)pTrans_->GetMathSize_x();
	ZSIZE = (int)pTrans_->GetMathSize_z();
	pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);
	Math_Resize(XSIZE, ZSIZE, &math_);

	if (pTrans_->GetTurnNum() % 2 == 0 && (int)pTrans_->GetSceneState() == SCENESTATE::SCENE_STAGE1_DELAY)
	{
		save_Num_ -= 1;
	}
	else if (pTrans_->GetTurnNum() % 2 == 0 && (int)pTrans_->GetSceneState() == SCENESTATE::SCENE_STAGE2_DELAY)
	{
		save_Num_ += 1;
	}
	else if (pTrans_->GetTurnNum() % 2 == 1 && (int)pTrans_->GetSceneState() == SCENESTATE::SCENE_STAGE1_DELAY)
	{
		save_Num_ += 1;
	}
	else
	{
		save_Num_ -= 1;
	}

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
	pTrans_ = (SceneTransition*)FindObject("SceneTransition");
	static Timer pTimer = Timer(30);
	pStage_ = (Stage*)FindObject("Stage");
	pPlayer_ = (Player*)FindObject("Player");
	if (pPlayer_->Is_Goal())
	{
		pTrans_->SetSceneState(pTrans_->GetSceneState() + 1);
		pTrans_->SetIsClear(player_Num_, true);
		pPlayer_->KillMe();
		pStage_->KillMe();
		KillMe();
	}
	if (pTimer.Time_Update() && false)
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
	std::string openfile = "saveMath";

	openfile += std::to_string(save_Num_);
	read.open(openfile, std::ios::in | std::ios::binary);
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

	openfile = "saveConvRot";

	openfile += std::to_string(save_Num_);
	read.open(openfile, std::ios::in | std::ios::binary);
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

XMFLOAT3 PlayScene::GetPlayerPos()
{
	pPlayer_ = (Player*)FindObject("Player");
	return pPlayer_->GetPosition();
}
