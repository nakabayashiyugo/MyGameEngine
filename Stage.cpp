#include <string>
#include "Stage.h"
#include "Engine/Input.h"
#include <vector>
#include "Engine/Model.h"
#include "Engine/Direct3D.h"

#include "resource.h"


Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), isRetturn_(false), retTgt_(0)
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
		for (int x = 0; x < XSIZE; x++)
		{
			for (int z = 0; z < ZSIZE; z++)
			{
				table_[x][z].rayDist = 999;
			}
		}
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
		//①　mousePosFront をベクトルに変換
		//②　①にinvVp, invProj, invViewをかける
		//③　mousePosBackをベクトルに変換
		//④　③にinvVp, invProj, invViewをかける
		//⑤　②から④に向かってレイをうつ(とりあえずモデル番号はhModel_[0]
		//⑥　レイが当たったらブレークポイントで止める

		XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
		vMouseFront = XMVector3TransformCoord(vMouseFront, invVp * invProj * invView);
		XMVECTOR  vMouseBack = XMLoadFloat3(&mousePosBack);
		vMouseBack = XMVector3TransformCoord(vMouseBack, invVp * invProj * invView);

		float prevDist = 999;
		actPos = XMFLOAT3(0, 0, 0);
		//すべてのtable_Historyの要素のIsColRayの中にtrueがあるかどうか
		bool isRayCol = false;
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
						isRayCol = true;
						break;
					}
				}
				if (table_[x][z].IsColRay)
				{
					if (prevDist > table_[x][z].rayDist)
					{
						actPos.x = x;
						actPos.z = z;

						prevDist = table_[x][z].rayDist;
					}
					table_[x][z].IsColRay = false;
				}
				
			}
		}
		if (isRayCol)
		{
			//table_Historyがいっぱいになった時最初のを消して前に詰める作業
			if (retTgt_ >= RET_CNT_LIMIT)
			{
				for (int hisCnt = 1; hisCnt < RET_CNT_LIMIT; hisCnt++)
				{
					for (int x = 0; x < XSIZE; x++)
					{
						for (int z = 0; z < ZSIZE; z++)
						{
							table_History[hisCnt - 1][x][z] = table_History[hisCnt][x][z];
						}
					}
				}
				retTgt_--;
			}
			//table_Historyに履歴を入れる
			for (int x = 0; x < XSIZE; x++)
			{
				for (int z = 0; z < ZSIZE; z++)
				{
					table_History[retTgt_][x][z] = table_[x][z];
				}
			}
			retTgt_++;
			switch (mode_)
			{
			case 0: table_[(int)actPos.x][(int)actPos.z].height++; break;
			case 1:
				if (table_[(int)actPos.x][(int)actPos.z].height > 1)
					table_[(int)actPos.x][(int)actPos.z].height--;
				break;
			case 2: 
				SetBlock((int)actPos.x, (int)actPos.z, (MODEL_TYPE)select_);
				break;
			}
		}
	}
	if (retTgt_)
	{
		if (isRetturn_)
		{

			int prevTableID = retTgt_ - 1;
			for (int x = 0; x < XSIZE; x++)
			{
				for (int z = 0; z < ZSIZE; z++)
				{
					table_[x][z] = table_History[prevTableID][x][z];
				}
			}
			retTgt_--;
			isRetturn_ = false;
		}
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

void Stage::TransTableHis(int _x, int _z, tableStruct* tabHis)
{
	
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
		switch (LOWORD(wp))
		{
		case 1018: mode_ = 0; break;
		case 1019: mode_ = 1; break;
		case 1020: mode_ = 2; break;
		case 1022: isRetturn_ = true; break;
		default: break;
		}
		
		select_ = (int)(SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_GETCURSEL, 0, 0));


		return TRUE;
	}
	return FALSE;
}
