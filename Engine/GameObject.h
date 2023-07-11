#pragma once
#include <list>
#include <string>
#include "Transform.h"

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

class GameObject
{
protected:
	std::list<GameObject*>	childList_;
	Transform				transform_;
	GameObject*				pParent_;
	std::string				objectName_;

	bool isDead_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	void UpdateSub();

	virtual void Draw() = 0;
	void DrawSub();

	virtual void Release() = 0;
	void ReleaseSub();
	template <class T>
	void Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		childList_.push_back(pObject);
	}

	void KillMe();
};