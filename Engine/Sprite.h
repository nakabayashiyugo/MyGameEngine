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
	//コンスタントバッファー
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
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ

	UINT64 indexNum_;
	std::vector<int> index_;

	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;
public:
	/// <summary>
	///  四角形を表すクラスのコンストラクタ
	/// </summary>
	Sprite();
	~Sprite();
	HRESULT Initialize();
	void Draw(Transform& transform);
	void Release();

private:
	virtual void InitVertexData();

	//俺が勝手に作ったやつです。
	void CalcVertexData();

	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture();

	void PassDataToCB(Transform& transform);
	void SetBufferToPipeline();
};

