#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Fbx;

//プレイシーンを管理するクラス
class Player
	: public GameObject
{
	Fbx* pFbx;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//デストラクタ
	~Player();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};