#pragma once
//�C���N���[�h

#include <d3d11.h>
#pragma comment(lib, "d3dcompiler.lib")


//�����J

#pragma comment(lib, "d3d11.lib")

namespace Direct3D

{

	//������

	void Initialize(int winW, int winH, HWND hWnd);



	//�`��J�n

	void BeginDraw();



	//�`��I��

	void EndDraw();



	//���

	void Release();

};

