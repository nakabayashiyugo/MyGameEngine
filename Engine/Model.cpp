#include "Model.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pFbx_;
		Transform transform_;
		std::string fileName_;
	};

	//���f���̃|�C���^�����Ă����|�C���^
	std::vector<ModelData*> modelList;
}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
}

int Model::Load(std::string filename)
{
	ModelData* pData = new ModelData();
	pData->fileName_ = filename;
	pData->pFbx_ = nullptr;
	for (auto itr = modelList.begin(); itr != modelList.end(); itr++)
	{
		if ((*itr)->fileName_ == filename)
		{
			pData->pFbx_ = (*itr)->pFbx_;
			break;
		}
	}
	if (pData->pFbx_ == nullptr)
	{
		pData->pFbx_ = new Fbx();
		pData->pFbx_->Load(filename);
	}
	modelList.push_back(pData);
	return (modelList.size() - 1);
}

void Model::Draw(int hModel)
{
	modelList[hModel]->pFbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false;
	for (int i = 0; i < modelList.size(); i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pFbx_ == modelList[j]->pFbx_)
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)
		{
			SAFE_DELETE(modelList[i]->pFbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();

}

void Model::RayCast(int hModel, RayCastData& rayData)
{
	modelList[hModel]->transform_.Calclation();
	//�@���[���h�s��̋t�s��
	XMMATRIX wInv = XMMatrixInverse(nullptr, modelList[hModel]->transform_.GetWorldMatrix());
	//�A���C�̒ʉߓ_�����߂�
	XMVECTOR vpass{ rayData.start.x + rayData.dir.x,
					rayData.start.y + rayData.dir.y,
					rayData.start.z + rayData.dir.z,
					rayData.start.w + rayData.dir.w };
	//�BrayData.start�����f����Ԃɕϊ�
	XMVECTOR vstart = XMLoadFloat4(&rayData.start);
	vstart = XMVector3TransformCoord(vstart, wInv);
	XMStoreFloat4(&rayData.start, vstart);
	//�C(�n�_��������x�N�g����L�΂�����)�ʉߓ_(�A)�ɇ@��������
	vpass = XMVector3TransformCoord(vpass, wInv);
	//�DrayData.dir���B����C�Ɍ������x�N�g��
	vpass = vpass - vstart;
	XMStoreFloat4(&rayData.dir, vpass);


	//�w�肳�ꂽ���f���ԍ���FBX�Ƀ��C�L���X�g
	modelList[hModel]->pFbx_->RayCast(rayData);
}
