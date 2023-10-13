#include <string>
#include "Stage.h"
#include "Engine/Input.h"
#include <vector>
#include "Engine/Model.h"
#include "Engine/Direct3D.h"

#include "resource.h"


Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), isRetturn_(false), retTgt_(0), 
	savefile_("default_Save")
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
		//���ׂĂ�table_History�̗v�f��IsColRay�̒���true�����邩�ǂ���
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
					trans.position_.x = (float)x;
					trans.position_.y = (float)y;
					trans.position_.z = (float)z;
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
						actPos.x = (float)x;
						actPos.z = (float)z;

						prevDist = table_[x][z].rayDist;
					}
					table_[x][z].IsColRay = false;
				}
				
			}
		}
		if (isRayCol)
		{
			std::vector<int[3][3]> a;
			a.resize(3);
			for(int i = 0; i < XSIZE; i++)
			{
				for (int j = 0; j < ZSIZE; j++)
				{
					table_History_.at(table_History_.size() - 1)[i][j] = table_[i][j];
				}
			}
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
		//���W�I�{�^���̏����l
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

		//�R���{�{�b�N�X�̏����l
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"�f�t�H���g");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"�y");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)"��");
		

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

void Stage::CreateNewTable()
{
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			SetBlock(x, z, MODEL_TYPE::MODEL_DEFAULT);
			SetHeight(x, z, 1);
			table_[x][z].IsColRay = false;
		}
	}
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
			write.write((char*)&table_[i][j].modelType, sizeof(table_[i]->modelType));
			write.write((char*)&table_[i][j].height, sizeof(table_[i]->height));
			//������ł͂Ȃ��f�[�^����������
		}
	}

	write.close();  //�t�@�C�������
}

void Stage::Read()
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
	ofn.Flags = OFN_FILEMUSTEXIST;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
	ofn.lpstrDefExt = "dat";                  	//�f�t�H���g�g���q

	//�u�t�@�C����ۑ��v�_�C�A���O
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

	int i = 0;
	while (!read.eof()) {  //�t�@�C���̍Ō�܂ő�����
		
		read.read((char*)&table_[i / XSIZE][i % ZSIZE].modelType, sizeof(table_[i / XSIZE][i % ZSIZE].modelType));
		read.read((char*)&table_[i / XSIZE][i % ZSIZE].height, sizeof(table_[i / XSIZE][i % ZSIZE].height));
		//������ł͂Ȃ��f�[�^��ǂ݂���
		
		i++;
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
