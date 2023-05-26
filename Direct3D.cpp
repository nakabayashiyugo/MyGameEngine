#include "Direct3D.h"

const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//変数
namespace Direct3D
{
	ID3D11Device* pDevice = nullptr;		//デバイス
	ID3D11DeviceContext* pContext = nullptr;		//デバイスコンテキスト
	IDXGISwapChain* pSwapChain = nullptr;		//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView = nullptr;	//レンダーターゲットビュー
}

//初期化
void Direct3D::Initialize(int winW, int winH, HWND hWnd)
{
    ///////////////////////////いろいろ準備するための設定///////////////////////////////
    //いろいろな設定項目をまとめた構造体
    DXGI_SWAP_CHAIN_DESC scDesc;

    //とりあえず全部0
    ZeroMemory(&scDesc, sizeof(scDesc));

    //描画先のフォーマット
    scDesc.BufferDesc.Width = WINDOW_WIDTH;		//画面幅
    scDesc.BufferDesc.Height = WINDOW_HEIGHT;	//画面高さ
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 何色使えるか

    //FPS（1/60秒に1回）
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;

    //その他
    scDesc.Windowed = TRUE;			//ウィンドウモードかフルスクリーンか
    scDesc.OutputWindow = hWnd;		//ウィンドウハンドル
    scDesc.BufferCount = 1;			//バックバッファの枚数
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//バックバッファの使い道＝画面に描画するために
    scDesc.SampleDesc.Count = 1;		//MSAA（アンチエイリアス）の設定
    scDesc.SampleDesc.Quality = 0;		//　〃
}

//描画開始
void Direct3D::BeginDraw()

{

}

//描画終了
void Direct3D::EndDraw()

{

}

//解放処理
void Direct3D::Release()

{

}