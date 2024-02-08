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
	XMFLOAT4 start;
	XMFLOAT4 dir;
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

	// ボーン構造体（関節情報）
	struct  Bone
	{
		XMMATRIX  bindPose;      // 初期ポーズ時のボーン変換行列
		XMMATRIX  newPose;       // アニメーションで変化したときのボーン変換行列
		XMMATRIX  diffPose;      // mBindPose に対する mNowPose の変化量
	};

	// ウェイト構造体（ボーンと頂点の関連付け）
	struct Weight
	{
		XMFLOAT3	posOrigin;		// 元々の頂点座標
		XMFLOAT3	normalOrigin;	// 元々の法線ベクトル
		int* pBoneIndex;		// 関連するボーンのID
		float* pBoneWeight;	// ボーンの重み
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

	//ボーン情報
	FbxSkin*		pSkinInfo_;		// スキンメッシュ情報（スキンメッシュアニメーションのデータ本体）
	FbxCluster**	ppCluster_;		// クラスタ情報（関節ごとに関連付けられた頂点情報）
	int				numBone_;		// FBXに含まれている関節の数
	Bone*			pBoneArray_;	// 各関節の情報
	Weight*			pWeightArray_;	// ウェイト情報（頂点の対する各関節の影響度合い）

public:

	Fbx();
	HRESULT Load(std::string fileName);

	HRESULT InitVertex(fbxsdk::FbxMesh* mesh);
	HRESULT InitIndex(fbxsdk::FbxMesh* mesh);		//インデックスバッファ準備
	HRESULT IntConstantBuffer();
	HRESULT InitMaterial(fbxsdk::FbxNode* node);
	HRESULT InitSkelton(FbxMesh* pMesh);			//骨の情報を準備

	void    Draw(Transform& transform);

	//ボーン有りのモデルを描画
	//引数：transform	行列情報
	//引数：time		フレーム情報（１アニメーション内の今どこか）
	void DrawSkinAnime(Transform& transform, FbxTime time);

	//任意のボーンの位置を取得
	//引数：boneName	取得したいボーンの位置
	//戻値：ボーンの位置
	XMFLOAT3 GetBonePosition(std::string boneName);

	//スキンメッシュ情報を取得
	//戻値：スキンメッシュ情報
	FbxSkin* GetSkinInfo() { return pSkinInfo_; }

	void    Release();

	void RayCast(RayCastData& rayData);
};