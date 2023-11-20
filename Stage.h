class TestScene;
#include "StageOrigin.h"

class Stage
	:public GameObject, StageOrigin
{
	int hModel_[MATH_MAX];
public:
	Stage(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	void SetBlock(int x, int z, MATHTYPE _type);

	
};

