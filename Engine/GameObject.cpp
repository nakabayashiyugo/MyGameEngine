#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name):childList_(0), isDead_(false)
{
	pParent_ = parent;
	objectName_ = name;
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

		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
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
		SAFE_DELETE((*itr)->pParent_);
		childList_.erase(itr);
		itr--;
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}
