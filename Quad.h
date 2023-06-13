#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Camera.h"
#include "Texture.h"

using namespace DirectX;

//コンスタントバッファー
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
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;

	int indNum_;

public:
	/// <summary>
	///  四角形を表すクラスのコンストラクタ
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

