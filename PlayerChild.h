#pragma once
#include "Engine/GameObject.h"

//プレイシーンを管理するクラス
class PlayerChild
	: public GameObject
{
	int hModel_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayerChild(GameObject* parent);

	//デストラクタ
	~PlayerChild();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void OnCollision(GameObject* pTarget) override;
};