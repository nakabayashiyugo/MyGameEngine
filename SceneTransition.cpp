#include "SceneTransition.h"
#include "MapEditScene.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"

SceneTransition::SceneTransition(GameObject* parent)
	: GameObject(parent, "SceneTransition"), sceneState_(SCENE_MAPEDIT1), turnNum_(0)
{
	XSIZE = (rand() % 15) + 5;
	ZSIZE = (rand() % 15) + 5;

	Math_Resize(XSIZE, ZSIZE, &math_);

	for (int x = 0; x < XSIZE; x++)
	{
		for (int y = 0; y < ZSIZE; y++)
		{
			math_[x][y].mathType_ = MATH_FLOOR;
			math_[x][y].converyor_rotate_ = 0;
		}
	}
	Write();
	sceneState_ = SCENE_MAPEDIT2;
	Write();
}

void SceneTransition::Initialize()
{
	sceneState_ = SCENE_MAPEDIT1;
}

void SceneTransition::Update()
{
	switch (sceneState_)
	{
	case SCENE_MAPEDIT1: turnNum_++; Instantiate<MapEditScene>(this); break;
	case SCENE_MAPEDIT2:Instantiate<MapEditScene>(this); break;
	case SCENE_STAGE:Instantiate<PlayScene>(this); break;
	default:
		break;
	}

}

void SceneTransition::Draw()
{
}

void SceneTransition::Release()
{
}

void SceneTransition::Write()
{
	std::ofstream write;
	std::string savefile = "saveMath";
	savefile += std::to_string((int)sceneState_ + 1);
	write.open(savefile, std::ios::out | std::ios::binary);

	//  ファイルが開けなかったときのエラー表示
	if (!write) {
		std::cout << "ファイル " << savefile << " が開けません";
		return;
	}

	for (int i = 0; i < XSIZE; i++) {
		for (int j = 0; j < ZSIZE; j++)
		{
			write.write((char*)&math_[i][j].mathType_, sizeof(math_[i][j].mathType_));
			//文字列ではないデータをかきこむ
		}
	}

	write.close();  //ファイルを閉じる

	savefile = "saveConvRot";
	savefile += std::to_string((int)sceneState_ + 1);
	write.open(savefile, std::ios::out | std::ios::binary);

	//  ファイルが開けなかったときのエラー表示
	if (!write) {
		std::cout << "ファイル " << savefile << " が開けません";
		return;
	}

	for (int i = 0; i < XSIZE; i++) {
		for (int j = 0; j < ZSIZE; j++)
		{
			write.write((char*)&math_[i][j].converyor_rotate_, sizeof(math_[i][j].converyor_rotate_));
			//文字列ではないデータをかきこむ
		}
	}

	write.close();  //ファイルを閉じる
}
