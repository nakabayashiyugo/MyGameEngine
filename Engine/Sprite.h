#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Direct3D.h"
#include "Camera.h"
#include "Texture.h"
#include "Transform.h"

using namespace DirectX;

class Sprite
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
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
	HRESULT Initialize(int winH, int winW);
	void Draw(Transform& transform, bool isShaft);
	void Release();

private:
	virtual void InitVertexData(int winH, int winW);

	//��������ɍ������ł��B
	void CalcVertexData(int winH, int winW);

	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture();

	void PassDataToCB(Transform& transform, bool isShaft);
	void SetBufferToPipeline();
};
