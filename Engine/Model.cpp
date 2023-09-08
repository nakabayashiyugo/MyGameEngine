#include "Model.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pFbx_;
		Transform transform_;
		std::string fileName_;
	};

	//モデルのポインタを入れておくポインタ
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
	modelList[hModel]->pFbx_->RayCast(rayData);
}
