#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include <vector>
#include "Transform.h"
#include "Direct3D.h"
#include "Camera.h"

class Texture;

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

struct RayCastData
{
	XMFLOAT3 start;
	XMFLOAT3 dir;
	bool hit;
	float dist;
};

class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4	diffuse;
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4    diffuseColor;		// ディフューズカラー（マテリアルの色）
		int		    isTexture;		// テクスチャ貼ってあるかどうか
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	VERTEX* pVertices_;
	int** ppIndex_;
	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
	std::vector <int> indexCount_;

public:

	Fbx();
	HRESULT Load(std::string fileName);

	HRESULT InitVertex(fbxsdk::FbxMesh* mesh);
	HRESULT InitIndex(fbxsdk::FbxMesh* mesh);		//インデックスバッファ準備
	HRESULT IntConstantBuffer();
	HRESULT InitMaterial(fbxsdk::FbxNode* node);

	void    Draw(Transform& transform);
	void    Release();

	void RayCast(RayCastData& rayData);
};