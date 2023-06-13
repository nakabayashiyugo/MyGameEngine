#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Camera.h"
#include "Texture.h"

using namespace DirectX;

//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Quad
{
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;

	int indNum_;

public:
	/// <summary>
	///  �l�p�`��\���N���X�̃R���X�g���N�^
	/// </summary>
	Quad();
	~Quad();
	virtual HRESULT Initialize();
	HRESULT MyCreateBuffer(VERTEX *_vertices, int _verNum, int *_index);
	virtual void Draw(XMMATRIX& worldMatrix);
	virtual void Release();
	void SetIndNum(int i);
	int GetIndNum();
};

