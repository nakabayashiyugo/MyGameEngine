#include <string>
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Direct3D.h"

#include "resource.h"

Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
	for (int i = 0; i < 5; i++)
	{
		hModel_[i] = -1;
	}
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			SetBlock(x, z, MODEL_TYPE::MODEL_DEFAULT);
			SetHeight(x, z, 1);
			table_[x][z].IsColRay = false;

			//model_Hit_In_Ray[x][z] = XMFLOAT3(0, 0, 0);
		}
	}
}

void Stage::Initialize()
{
	std::string modelName[MODEL_NUM] =
	{ 
	 "BoxDefault.fbx",
	 "BoxBrick.fbx",
	 "BoxGrass.fbx",
	 "BoxSand.fbx",
	 "BoxWater.fbx"
	};
	std::string fname_base = "Assets\\";
	//モデルデータのロード
	for (int i = 0; i < MODEL_NUM; i++)
	{
		hModel_[i] = Model::Load(fname_base + modelName[i]);
		assert(hModel_[i] >= 0);
	}
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			SetBlock(x, z, (MODEL_TYPE)(x/3));
		}
	}
}

void Stage::Update()
{
	
	if (Input::IsMouseButtonDown(0))
	{
		float w = (float)(Direct3D::scrWidth / 2);
		float h = (float)(Direct3D::scrHeight / 2);
		XMMATRIX vp =
		{
			w,  0, 0, 0,
			0, -h, 0, 0,
			0,  0, 1, 0,
			w,  h, 0, 1
		};

		//ビューポート
		XMMATRIX invVp = XMMatrixInverse(nullptr, vp);
		//プロジェクション変換
		XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
		//ビュー変換
		XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
		XMFLOAT3 mousePosFront = Input::GetMousePosition();
		mousePosFront.z = 0.0f;
		XMFLOAT3 mousePosBack = Input::GetMousePosition();
		mousePosBack.z = 1.0f;
		//�@　mousePosFront をベクトルに変換
		//�A　�@にinvVp, invProj, invViewをかける
		//�B　mousePosBackをベクトルに変換
		//�C　�BにinvVp, invProj, invViewをかける
		//�D　�Aから�Cに向かってレイをうつ(とりあえずモデル番号はhModel_[0]
		//�E　レイが当たったらブレークポイントで止める

		XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
		vMouseFront = XMVector3TransformCoord(vMouseFront, invVp * invProj * invView);
		XMVECTOR  vMouseBack = XMLoadFloat3(&mousePosBack);
		vMouseBack = XMVector3TransformCoord(vMouseBack, invVp * invProj * invView);

		float prevDist = 999, Dist = 999;
		int actPosX = 0, actPosZ = 0;
		bool Israycol = false;
		for (int x = 0; x < XSIZE; x++)
		{
			for (int z = 0; z < ZSIZE; z++)
			{
				for (int y = 0; y < table_[x][z].height; y++)
				{
					RayCastData data;
					XMStoreFloat4(&data.start, vMouseFront);
					XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);
					Transform trans;
					trans.position_.x = x;
					trans.position_.y = y;
					trans.position_.z = z;
					Model::SetTransform(hModel_[0], trans);

					Model::RayCast(hModel_[0], data);

					if (data.hit)
					{
						if (table_[x][z].rayDist > data.dist)
							table_[x][z].rayDist = data.dist;
						table_[x][z].IsColRay = true;
						Israycol = true;
						break;
					}
				}
				if (table_[x][z].IsColRay)
				{
					Dist = table_[x][z].rayDist;
					if (prevDist > Dist)
					{
						actPosX = x;
						actPosZ = z;

						prevDist = Dist;
					}
					table_[x][z].IsColRay = false;
				}
			}
		}
		if(Israycol)
			table_[actPosX][actPosZ].height++;
	}
}

void Stage::Draw()
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			for (int y = 0; y < table_[x][z].height; y++)
			{
				transform_.position_ = XMFLOAT3((float)x, y, (float)z);
				int type = table_[x][z].modelType;
				Model::SetTransform(hModel_[type], transform_);
				Model::Draw(hModel_[type]);
			}
		}
	}
	
}

void Stage::Release()
{
}

void Stage::SetBlock(int x, int z, MODEL_TYPE _type)
{
	table_[x][z].modelType = _type;
	assert(_type <= MODEL_TYPE::MODEL_MAX);
}

void Stage::SetHeight(int x, int z, int _height)
{
	table_[x][z].height = _height;
}

BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		//ラジオボタンの初期値
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

		//コンボボックスの初期値
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"デフォルト");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"石");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"草");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"土");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"水");
		

		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);

		return TRUE;

	case WM_COMMAND:
		mode_ = LOWORD(wp) - IDC_RADIO_UP;
		
		select_ = (int)(SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_GETCURSEL, 0, 0));
		return TRUE;
	}
	return FALSE;
}
