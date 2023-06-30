//インクルード
#include <Windows.h>
#include <d3d11.h>
#include <string>
#include "Direct3D.h"
#include "Input.h"
#include "Quad.h"
#include "Dice.h"
#include "Sprite.h"
#include "Camera.h"
#include "Transform.h"
#include "Fbx.h"


//リンカ
#pragma comment(lib, "d3d11.lib")

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const char* GAME_TITLE = "サンプルゲーム";
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

ID3D11Device*           pDevice_;		//デバイス
ID3D11DeviceContext*    pContext_;		//デバイスコンテキスト
IDXGISwapChain*         pSwapChain_;		//スワップチェイン
ID3D11RenderTargetView* pRenderTargetView_;	//レンダーターゲットビュー

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    //ウィンドウクラス（設計図）を作成
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
    wc.hInstance = hInstance;                   //インスタンスハンドル
    wc.lpszClassName = WIN_CLASS_NAME;            //ウィンドウクラス名
    wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
    wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
    wc.hIcon = LoadIcon(NULL, IDI_QUESTION);        //アイコン
    wc.hIconSm = LoadIcon(NULL, IDI_QUESTION);   //小さいアイコン
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
    wc.lpszMenuName = NULL;                     //メニュー（なし）
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）

    RegisterClassEx(&wc);  //クラスを登録

    //ウィンドウサイズの計算
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     //ウィンドウ幅
    int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

  //ウィンドウを作成
    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //ウィンドウクラス名
        GAME_TITLE,     //タイトルバーに表示する内容
        WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
        CW_USEDEFAULT,       //表示位置左（おまかせ）
        CW_USEDEFAULT,       //表示位置上（おまかせ）
        winW,                 //ウィンドウ幅
        winH,                 //ウィンドウ高さ
        NULL,                //親ウインドウ（なし）
        NULL,                //メニュー（なし）
        hInstance,           //インスタンス
        NULL                 //パラメータ（なし）
    );

  //ウィンドウを表示
    ShowWindow(hWnd, nCmdShow);

    HRESULT hr;

    //Direct3D初期化
    hr = Direct3D::Initialize(winW, winH, hWnd);
    if (FAILED(hr))
    {
        //失敗したときの処理
        PostQuitMessage(0);
    }
    Input::Initialize(hWnd);

    //カメラ、起動
    Camera::Initialize();

    //Camera::SetPosition(XMFLOAT3(0, 0, -10));
    Camera::SetTarget(XMFLOAT3(0, 0, 0));

    

    //ポリゴンクラス作ってる
    // 
    //Quad* pQuad = new Quad();
    //hr = pQuad->Initialize();
    //if (FAILED(hr))
    //{
    //    //失敗したときの処理
    //    PostQuitMessage(0);
    //}

    //Dice* pDice = new Dice();
    //hr = pDice->Initialize();
    //if (FAILED(hr))
    //{
    //    //失敗したときの処理
    //    PostQuitMessage(0);
    //}

    //Sprite* pSprite = new Sprite();
    //hr = pSprite->Initialize(WINDOW_HEIGHT, WINDOW_WIDTH);
    //if (FAILED(hr))
    //{
    //    //失敗したときの処理
    //    PostQuitMessage(0);
    //}

    //FBX　ロード
    Fbx* pFbx = new Fbx();
    std::string oden = "Assets/Oden2.fbx";
    hr = pFbx->Load(oden);
    if (FAILED(hr))
    {
        //失敗したときの処理
        PostQuitMessage(0);
    }


  //メッセージループ（何か起きるのを待つ）
    
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //メッセージなし
        else
        {
            //カメラ、更新
            Camera::Update();

            //ゲームの処理
            Direct3D::BeginDraw();

            Input::Update();

            //XMMATRIX mat = XMMatrixIdentity();
            //XMMATRIX diceMat = pTransform->GetWorldMatrix();
            //pDice->Draw(pTransform);
            //pQuad->Draw(mat);
            //pSprite->Draw(mat);

            static float angle = 0;

            angle += 0.05f;

            //Transform diceTransform;
            //diceTransform.position_.y = 3.0f;
            //diceTransform.rotate_.y = angle;
            //pDice->Draw(diceTransform);
            ////
            //mat = XMMatrixScaling(512.0f / 800.0f, 256.0f / 600.0f, 1.0f);
            //Transform spriteTransform;
            //spriteTransform.scale_.x = 1;
            //spriteTransform.scale_.y = 1;
            ////
            //mat = XMMatrixScaling(512.0f/800.0f, 256.0f/600.0f, 1.0f);
            //pSprite->Draw(spriteTransform);
            Transform diceTransform;
            diceTransform.position_.y = -2.0f;
            diceTransform.rotate_.y = angle;
            pFbx->Draw(diceTransform);

            if (Input::IsKey(DIK_ESCAPE))
            {
                PostQuitMessage(0);
            }

            //描画処理
            Direct3D::EndDraw();
        }
    }

    //解放処理
    Direct3D::Release();
    Input::Release();
    //SAFE_DELETE(pQuad);
    //SAFE_DELETE(pDice);
    //SAFE_DELETE(pSprite);
    SAFE_RELEASE(pFbx);

	return 0;
}


//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);  //プログラム終了
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}