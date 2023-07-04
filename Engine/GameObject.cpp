#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name): childList_(0), transform_()
{
	pParent_ = parent;
	objectName_ = name;
}

GameObject::~GameObject()
{
}
