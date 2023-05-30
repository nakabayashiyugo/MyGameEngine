#pragma once
//インクルード
#include <d3dcompiler.h>

#include <d3d11.h>
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3dcompiler.lib")

//リンカ

#pragma comment(lib, "d3d11.lib")

namespace Direct3D

{
	extern ID3D11Device* pDevice;		//デバイス
	//初期化

	void Initialize(int winW, int winH, HWND hWnd);

	//シェーダー準備

	void InitShader();

	//描画開始

	void BeginDraw();



	//描画終了

	void EndDraw();



	//解放

	void Release();


};

