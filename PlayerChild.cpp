#include "PlayerChild.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

PlayerChild::PlayerChild(GameObject* parent)
	: GameObject(parent, "PlayerChild"), hModel_(-1)
{
}

PlayerChild::~PlayerChild()
{
}

void PlayerChild::Initialize()
{
	hModel_ = Model::Load("Assets\\oden2.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);

	transform_.rotate_.x = 90;

	SphereCollider* col = new SphereCollider(1.0);
	AddCollider(col);
}

void PlayerChild::Update()
{
	transform_.rotate_.z++;
	transform_.position_.z += 0.5f;
	if (transform_.position_.z >= 50)
	{
		KillMe();
	}
}

void PlayerChild::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void PlayerChild::Release()
{
}

void PlayerChild::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Enemy")
	{
		pTarget->KillMe();
		this->KillMe();
	}
}