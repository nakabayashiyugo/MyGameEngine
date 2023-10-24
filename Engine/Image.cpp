#include "Image.h"
#include "Sprite.h"

namespace Image
{
	struct ImageData
	{
		Sprite* pSprite_;
		Transform transform_;
		std::string fileName_;
	};

	//モデルのポインタを入れておくポインタ
	std::vector<ImageData*> imageList;
}

void Image::SetTransform(int hImage, Transform transform)
{
	imageList[hImage]->transform_ = transform;
}

int Image::Load(std::string filename)
{
	ImageData* pData = new ImageData();
	pData->fileName_ = filename;
	pData->pSprite_ = nullptr;
	for (auto itr = imageList.begin(); itr != imageList.end(); itr++)
	{
		if ((*itr)->fileName_ == filename)
		{
			pData->pSprite_ = (*itr)->pSprite_;
			break;
		}
	}
	if (pData->pSprite_ == nullptr)
	{
		pData->pSprite_ = new Sprite();
		pData->pSprite_->Load(filename);
	}
	imageList.push_back(pData);
	return (imageList.size() - 1);
}

void Image::Draw(int hImage)
{
	imageList[hImage]->pSprite_->Draw(imageList[hImage]->transform_);
}

void Image::Release()
{
	bool isReffered = false;
	for (int i = 0; i < imageList.size(); i++)
	{
		for (int j = i + 1; j < imageList.size(); j++)
		{
			if (imageList[i]->pSprite_ == imageList[j]->pSprite_)
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)
		{
			SAFE_DELETE(imageList[i]->pSprite_);
		}
		SAFE_DELETE(imageList[i]);
	}
	imageList.clear();

}
