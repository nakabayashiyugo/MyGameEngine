#include "Direct3D.h"

const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���

//�ϐ�
namespace Direct3D
{
	ID3D11Device* pDevice = nullptr;		//�f�o�C�X
	ID3D11DeviceContext* pContext = nullptr;		//�f�o�C�X�R���e�L�X�g
	IDXGISwapChain* pSwapChain = nullptr;		//�X���b�v�`�F�C��
	ID3D11RenderTargetView* pRenderTargetView = nullptr;	//�����_�[�^�[�Q�b�g�r���[
}

//������
void Direct3D::Initialize(int winW, int winH, HWND hWnd)
{
    ///////////////////////////���낢�돀�����邽�߂̐ݒ�///////////////////////////////
    //���낢��Ȑݒ荀�ڂ��܂Ƃ߂��\����
    DXGI_SWAP_CHAIN_DESC scDesc;

    //�Ƃ肠�����S��0
    ZeroMemory(&scDesc, sizeof(scDesc));

    //�`���̃t�H�[�}�b�g
    scDesc.BufferDesc.Width = WINDOW_WIDTH;		//��ʕ�
    scDesc.BufferDesc.Height = WINDOW_HEIGHT;	//��ʍ���
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ���F�g���邩

    //FPS�i1/60�b��1��j
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;

    //���̑�
    scDesc.Windowed = TRUE;			//�E�B���h�E���[�h���t���X�N���[����
    scDesc.OutputWindow = hWnd;		//�E�B���h�E�n���h��
    scDesc.BufferCount = 1;			//�o�b�N�o�b�t�@�̖���
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�o�b�N�o�b�t�@�̎g��������ʂɕ`�悷�邽�߂�
    scDesc.SampleDesc.Count = 1;		//MSAA�i�A���`�G�C���A�X�j�̐ݒ�
    scDesc.SampleDesc.Quality = 0;		//�@�V
}

//�`��J�n
void Direct3D::BeginDraw()

{

}

//�`��I��
void Direct3D::EndDraw()

{

}

//�������
void Direct3D::Release()

{

}