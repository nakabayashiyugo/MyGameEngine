#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include "Direct3D.h"
#include "Camera.h"

class Texture;

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
public:

	Fbx();
	HRESULT Load(std::string fileName);

	HRESULT InitVertex(fbxsdk::FbxMesh* mesh);
	HRESULT InitIndex(fbxsdk::FbxMesh* mesh);		//�C���f�b�N�X�o�b�t�@����
	HRESULT IntConstantBuffer();
	HRESULT InitMaterial(fbxsdk::FbxNode* node);

	void    Draw(Transform& transform);
	void    Release();
};