class PlayScene;
class Togetoge;
#include "StageOrigin.h"

class Stage
	:public GameObject, StageOrigin
{
	int hModel_[MATH_MAX];

	bool isStandPitfall_;

	float makeHoleTime_;

	PlayScene* pPlayScene_;

	std::vector<Togetoge*> pTgtg_;
public:
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetBlock(int x, int z, MATHTYPE _type);

	void SetTableMath(std::vector<std::vector<MATHDEDAIL>> _math);

	void Write();
};

