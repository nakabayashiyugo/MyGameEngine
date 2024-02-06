class PlayScene;
class Togetoge;
#include "StageOrigin.h"

class Stage
	:public GameObject, StageOrigin
{
	int hModel_[MATH_MAX];
	int save_Num_;

	bool isStandPitfall_;

	float makeHoleTime_;

	PlayScene* pPlayScene_;

	std::vector<Togetoge*> pTgtg_;

	XMFLOAT3 tgtgGivePos_;
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

	XMFLOAT3 GetTogetogeInitPos() { return tgtgGivePos_; }

	XMFLOAT3 GetTogetogeDestPos(XMFLOAT3 _pos)
	{
		auto itr = tTgtgRoute_.begin();
		while (itr != tTgtgRoute_.end())
		{
			if ((int)itr->initPos_.x == _pos.x &&
				(int)itr->initPos_.y == _pos.z)
			{
				return XMFLOAT3(itr->destPos_.x, 0, itr->destPos_.y);
			}
		}
		return XMFLOAT3();
	}

	void Write();
	void Read();
};

