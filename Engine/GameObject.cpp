#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(nullptr), isDead_(false)
{
	objectName_ = name;
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}

void GameObject::SetTransformPos(XMFLOAT3 pos)
{
	transform_.position_ = pos;
}

void GameObject::SetTransformRot(XMFLOAT3 rot)
{
	transform_.rotate_ = rot;
}

void GameObject::SetTransformSca(XMFLOAT3 sca)
{
	transform_.scale_ = sca;
}

Transform GameObject::GetTransform()
{
	return transform_;
}

