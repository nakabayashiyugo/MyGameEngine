#include "Engine/GameObject.h"

class Togetoge
	:public GameObject
{
	int hModel_;
public:
	Togetoge(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetPosition(XMFLOAT3 pos) { transform_.position_ = pos; }
};

