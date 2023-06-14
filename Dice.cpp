#include "Dice.h"

HRESULT Dice::Initialize()
{
	HRESULT hr;
	// 頂点情報
	VERTEX vertices[] =
	{
		//前面
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)  },//左上
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),	XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f) },//右上
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f)  },//右下
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) , XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f) },//左下
		//上面
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)  },//左上
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)  },//右上
		{XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)  },//左上奥
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)  },//右上奥
		//右側面
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),	XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },//右上
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)  },//右下
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f),  XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)  },//右上奥
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f),  XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)  },//右下奥
		//左側面
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f), XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)  },//左上
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),  XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)  },//左下
		{XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f),   XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)  },//左上奥
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),   XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f)  },//左下奥
		//後面
		{XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) ,  XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) },//左上奥
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)  },//右上奥
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f),  XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)  },//右下奥
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f),   XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)  },//左下奥
		//下面
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f),  XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)  },//左下
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),   XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)  },//右下
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f),   XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)  },//右下奥
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f),  XMVectorSet(0.0f,-1.0f,0.0f, 0.0f)  },//左下奥

	};

	//インデックス情報
	int index[] = { 0,1,2, 0,2,3, //前面
					4,6,7, 4,7,5, //上面
					8,10,9, 10,11,9, //右側面
					12,13,15, 12,15,14, //左側面
					16,18,17, 16,19,18, //後面
					20,21,22, 20,22,23, //下面
	};

	SetIndNum(sizeof(index) / sizeof(index[0]));

	hr = MyCreateBuffer(vertices, sizeof(vertices) / sizeof(vertices[0]), index);
	if (FAILED(hr))
	{
		//エラー処理
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	return S_OK;
}
