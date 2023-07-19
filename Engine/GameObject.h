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
	//コンストラクタ・デストラクタ
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

public:
	//基本的な奴
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	void UpdateSub();
	virtual void Draw() = 0;
	void DrawSub();
	virtual void Release() = 0;
	void ReleaseSub();

public:
	//テンプレートの定義
	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}

public:
	//transformのセッター
	void SetTransformPos(XMFLOAT3 pos);
	void SetTransformRot(XMFLOAT3 rot);
	void SetTransformSca(XMFLOAT3 sca);

	Transform GetTransform();

public:
	//オブジェクト探すためのやつ
	GameObject* FindChildObject(std::string _objName);
	GameObject* GetRootJob();
	GameObject* FindObject(std::string _objName);

	void KillMe();
};