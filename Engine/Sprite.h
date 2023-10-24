#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Direct3D.h"
#include "Camera.h"
#include "Texture.h"
#include "Transform.h"

using namespace DirectX;

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Sprite
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
		XMMATRIX	uvTrans;	// �e�N�X�`�����W�ϊ��s��
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
protected:
	UINT64 vertexNum_;
	std::vector<VERTEX> vertices_;
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@

	UINT64 indexNum_;
	std::vector<int> index_;

	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;
public:
	/// <summary>
	///  �l�p�`��\���N���X�̃R���X�g���N�^
	/// </summary>
	Sprite();
	~Sprite();
	HRESULT Load(std::string _filename);
	void Draw(Transform& transform, RECT _rect);
	void Release();

private:
	virtual void InitVertexData();

	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	void PassDataToCB(Transform& transform, RECT _rect);
	void SetBufferToPipeline();
};

