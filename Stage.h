class PlayScene;
#include "StageOrigin.h"

class Stage
	:public GameObject, StageOrigin
{
	int hModel_[MATH_MAX];

	PlayScene* pPlayScene_;
public:
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetBlock(int x, int z, MATHTYPE _type);

	void SetTableMath(std::vector<std::vector<MATHDEDAIL>> _math);

	void Write();
};

