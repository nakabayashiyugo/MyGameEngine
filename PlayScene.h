#pragma once
#include "Engine/GameObject.h"
#include "StageOrigin.h"

class Stage;
class Player;

class PlayScene
	:public GameObject, StageOrigin
{
	Stage* pStage_;
	Player* pPlayer_;

	bool table_Change_;
public:
	PlayScene(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	void Read();

	std::vector<std::vector<MATHDEDAIL>> GetTableMath() { return math_; }

	XMFLOAT3 GetPlayerPos();

	void SetTableChange(bool _table_change) { table_Change_ = _table_change; }
	bool GetTableChange() { return table_Change_; }
};