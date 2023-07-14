#include "Model.h"
#include "Engine/Fbx.h"

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
}

int Model::Load(std::string filename)
{
	ModelData* pData = new ModelData();
	pData->fileName_ = filename;
	pData->pFbx_ = nullptr;
	for (auto itr = modelList.begin(); itr == modelList.end(); itr++)
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
