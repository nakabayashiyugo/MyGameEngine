#include <string>
#include <vector>
#include <array>
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Direct3D.h"
#include "TestScene.h"
#include "Engine/RootJob.h"

#include "resource.h"

Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), isRedo_(false), isUndo_(false), curHistory_Target_(0),
	savefile_("default_Save")
{
	for (int i = 0; i < 5; i++)
	{
		hModel_[i] = -1;
	}
	pTest = (TestScene*)FindObject("TestScene");
	XSIZE = pTest->GetTableXSIZE();
	ZSIZE = pTest->GetTableZSIZE();
	for (int x = 0; x < XSIZE; x++)
	{
		table_.resize(x + 1);
		for (int z = 0; z < ZSIZE; z++)
		{
			table_.at(x).resize(z + 1);
			SetBlock(x, z, MODEL_TYPE::MODEL_DEFAULT);
			SetHeight(x, z, 1);
			table_[x][z].isRayHit = false;
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
	//���f���f�[�^�̃��[�h
	for (int i = 0; i < MODEL_NUM; i++)
	{
		hModel_[i] = Model::Load(fname_base + modelName[i]);
		assert(hModel_[i] >= 0);
	}
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			SetBlock(x, z, (MODEL_TYPE)(x % MODEL_NUM));
		}
	}
}

void Stage::Update()
{
	switch (mode_)
	{
	case 0:
	case 1:
		if (Input::IsMouseButtonDown(0))
		{
			TableChange();
		}
		break;
	case 2:
		if (Input::IsMouseButton(0))
		{
			TableChange();
		}
		break;
	}
	if (isRedo_ && curHistory_Target_ != 0)
	{
		MODEL_TYPE tmpMT;
		int tmpHI;
		tmpMT = table_[table_History[curHistory_Target_ - 1].pos.x]
			[table_History[curHistory_Target_ - 1].pos.z].modelType;
		table_[table_History[curHistory_Target_ - 1].pos.x]
			[table_History[curHistory_Target_ - 1].pos.z].modelType = table_History[curHistory_Target_ - 1].modelType;
		table_History[curHistory_Target_ - 1].modelType = tmpMT;

		tmpHI = table_[table_History[curHistory_Target_ - 1].pos.x]
			[table_History[curHistory_Target_ - 1].pos.z].height;
		table_[table_History[curHistory_Target_ - 1].pos.x]
			[table_History[curHistory_Target_ - 1].pos.z].height = table_History[curHistory_Target_ - 1].height;
		table_History[curHistory_Target_ - 1].height = tmpHI;

		curHistory_Target_--;
		isRedo_ = false;
	}
	if (isUndo_ && curHistory_Target_ < table_History.size())
	{
		MODEL_TYPE tmpMT;
		int tmpHI;
		tmpMT = table_[table_History[curHistory_Target_].pos.x]
			[table_History[curHistory_Target_].pos.z].modelType;
		table_[table_History[curHistory_Target_].pos.x]
			[table_History[curHistory_Target_].pos.z].modelType = table_History[curHistory_Target_].modelType;
		table_History[curHistory_Target_].modelType = tmpMT;

		tmpHI = table_[table_History[curHistory_Target_].pos.x]
			[table_History[curHistory_Target_].pos.z].height;
		table_[table_History[curHistory_Target_].pos.x]
			[table_History[curHistory_Target_].pos.z].height = table_History[curHistory_Target_].height;
		table_History[curHistory_Target_].height = tmpHI;

		curHistory_Target_++;
		isUndo_ = false;
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
				transform_.position_ = XMFLOAT3((float)x, (float)y, (float)z);
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
	table_.at(x).at(z).modelType = _type;
	assert(_type <= MODEL_TYPE::MODEL_MAX);
}

void Stage::SetHeight(int x, int z, int _height)
{
	table_[x][z].height = _height;
}



BOOL Stage::CreateTableDialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	char* X_MathNum = NULL;
	char* Z_MathNum = NULL;
	char bufX[3], bufZ[3];
	for (int i = 0; i < 3; i++)
	{
		bufX[i] = '0';
		bufZ[i] = '0';
	}
	int xmathnum;
	int zmathnum;
	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case 1027: 
			GetDlgItemText(hDlg, IDC_EDIT_X_MATHNUM,(LPTSTR)X_MathNum, (int)sizeof(X_MathNum));
			GetDlgItemText(hDlg, IDC_EDIT_Z_MATHNUM,(LPTSTR)Z_MathNum, (int)sizeof(Z_MathNum));
			strncpy_s(bufX, X_MathNum, (int)sizeof(X_MathNum));
			strncpy_s(bufZ, Z_MathNum, (int)sizeof(Z_MathNum));
			xmathnum = std::atoi(bufX);
			zmathnum = std::atoi(bufZ);
			CreateNewTable(xmathnum, zmathnum);
			EndDialog(hDlg, 0);
			return TRUE;
		case 1028: EndDialog(hDlg, 0); return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

void Stage::TableChange()
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

	//�r���[�|�[�g
	XMMATRIX invVp = XMMatrixInverse(nullptr, vp);
	//�v���W�F�N�V�����ϊ�
	XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
	//�r���[�ϊ�
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;
	//�@�@mousePosFront ���x�N�g���ɕϊ�
	//�A�@�@��invVp, invProj, invView��������
	//�B�@mousePosBack���x�N�g���ɕϊ�
	//�C�@�B��invVp, invProj, invView��������
	//�D�@�A����C�Ɍ������ă��C������(�Ƃ肠�������f���ԍ���hModel_[0]
	//�E�@���C������������u���[�N�|�C���g�Ŏ~�߂�

	XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
	vMouseFront = XMVector3TransformCoord(vMouseFront, invVp * invProj * invView);
	XMVECTOR  vMouseBack = XMLoadFloat3(&mousePosBack);
	vMouseBack = XMVector3TransformCoord(vMouseBack, invVp * invProj * invView);

	float prevDist = 999;
	actPos = XMFLOAT3(0, 0, 0);
	//���ׂĂ�table_History�̗v�f��isRayHit�̒���true�����邩�ǂ���
	bool isRayHit_AllBlocks = false;

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
				trans.position_.x = (float)x;
				trans.position_.y = (float)y;
				trans.position_.z = (float)z;
				Model::SetTransform(hModel_[0], trans);

				Model::RayCast(hModel_[0], data);

				if (data.hit)
				{
					if (table_[x][z].rayDist > data.dist)
						table_[x][z].rayDist = data.dist;
					table_[x][z].isRayHit = true;
					isRayHit_AllBlocks = true;
					break;
				}
			}
			if (table_[x][z].isRayHit)
			{
				if (prevDist > table_[x][z].rayDist)
				{
					actPos.x = (float)x;
					actPos.z = (float)z;

					prevDist = table_[x][z].rayDist;
				}
				table_[x][z].isRayHit = false;
			}

		}
	}
	if (isRayHit_AllBlocks)
	{
		int eraseNum = (int)table_History.size();
		for (int i = curHistory_Target_; i < eraseNum; i++)
		{
			table_History.erase(table_History.end() - 1);
		}
		curHistory_Target_++;
		table_History.resize(table_History.size() + 1);
		table_History[table_History.size() - 1].modelType = table_[(int)actPos.x][(int)actPos.z].modelType;
		table_History[table_History.size() - 1].height = table_[(int)actPos.x][(int)actPos.z].height;
		table_History[table_History.size() - 1].pos.x = (int)actPos.x;
		table_History[table_History.size() - 1].pos.z = (int)actPos.z;
		
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
		if (table_History[table_History.size() - 1].modelType == table_[(int)actPos.x][(int)actPos.z].modelType &&
			table_History[table_History.size() - 1].height == table_[(int)actPos.x][(int)actPos.z].height &&
			table_History[table_History.size() - 1].pos.x == actPos.x &&
			table_History[table_History.size() - 1].pos.z == actPos.z)
		{
			curHistory_Target_--;
			table_History.erase(table_History.end() - 1);
		}
	}
}

void Stage::DeleteTableHistory()
{
	curHistory_Target_ = 0;
	for (auto itr = table_History.begin(); itr != table_History.end();)
	{
		itr = table_History.erase(itr);
	}
}

void Stage::CreateNewTable(int _xmath, int _zmath)
{
	DeleteTableHistory();
	TestScene* pTest = (TestScene*)FindObject("TestScene");
	pTest->SetTableSize(_xmath, _zmath);
	pTest->SetCreateNewTable(true);
	KillMe();
}

void Stage::Write()
{
	std::ofstream write;
	write.open(savefile_, std::ios::out | std::ios::binary);

	//  �t�@�C�����J���Ȃ������Ƃ��̃G���[�\��
	if (!write) {
		std::cout << "�t�@�C�� " << savefile_ << " ���J���܂���";
		return;
	}

	for (int i = 0; i < XSIZE; i++) {
		for (int j = 0; j < ZSIZE; j++)
		{
			write.write((char*)&table_[i][j].modelType, sizeof(table_.at(i).at(j).modelType));
			write.write((char*)&table_[i][j].height, sizeof(table_.at(i).at(j).height));
			//������ł͂Ȃ��f�[�^����������
		}
	}

	write.close();  //�t�@�C�������
}

void Stage::Read()
{
	DeleteTableHistory();
	char fileName[MAX_PATH] = "����.map";  //�t�@�C����������ϐ�

	OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
	ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
	ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
	ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.dat)\0*.dat\0")        //�����t�@�C���̎��
		TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
	ofn.lpstrFile = fileName;               	//�t�@�C����
	ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
	ofn.Flags = OFN_FILEMUSTEXIST;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
	ofn.lpstrDefExt = "dat";                  	//�f�t�H���g�g���q

	BOOL selFile;
	selFile = GetOpenFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;

	savefile_ = fileName;


	//modelType�t�@�C���ǂݍ���
	std::ifstream read(savefile_, std::ios::in | std::ios::binary);
	//  �t�@�C�����J��
	//  ios::in �͓ǂݍ��ݐ�p  ios::binary �̓o�C�i���`��

	if (!read) {
		std::cout << "�t�@�C�� " << savefile_ << " ���J���܂���";
		return;
	}
	//  �t�@�C�����J���Ȃ������Ƃ��̑΍�

	//�t�@�C���̍Ō�܂ő�����
	for (int i = 0; i < XSIZE; i++) 
	{
		for (int j = 0; j < ZSIZE; j++)
		{
			read.read((char*)&table_[i][j].modelType, sizeof(table_.at(i).at(j).modelType));
			read.read((char*)&table_[i][j].height, sizeof(table_.at(i).at(j).height));
			//������ł͂Ȃ��f�[�^��ǂ݂���

		}
	}
	read.close();  //�t�@�C�������
}

void Stage::SaveAs()
{
	char fileName[MAX_PATH] = "����.map";  //�t�@�C����������ϐ�

	//�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
	OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
	ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
	ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
	ofn.lpstrFilter = TEXT("�}�b�v�f�[�^(*.dat)\0*.dat\0")        //�����t�@�C���̎��
		TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
	ofn.lpstrFile = fileName;               	//�t�@�C����
	ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
	ofn.Flags = OFN_OVERWRITEPROMPT;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
	ofn.lpstrDefExt = "dat";                  	//�f�t�H���g�g���q

	//�u�t�@�C����ۑ��v�_�C�A���O
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;

	savefile_ = fileName;

	Write();
}
