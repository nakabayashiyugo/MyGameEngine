#include "Dice.h"

HRESULT Dice::Initialize()
{
	HRESULT hr;
	// ���_���
	VERTEX vertices[] =
	{
		//�O��
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },//����
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),	XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },//�E��
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },//�E��
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) },//����
		//���
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },//����
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) },//�E��
		{XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },//���㉜
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),	XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },//�E�㉜
		//�E����
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),	XMVectorSet(0.5f, 0.0f, 0.0f, 0.0f) },//�E�㉜
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },//�E����
		//������
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },//����
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },//����
		{XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f) },//���㉜
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },//������
		//���
		{XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), XMVectorSet(0.5f, 0.5f, 0.0f, 0.0f) },//���㉜
		{XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f),	XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },//�E�㉜
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f) },//�E����
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.5f, 1.0f, 0.0f, 0.0f) },//������
		//����
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f),XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f) },//����
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f),	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },//�E��
		{XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(1.0f, 0.5f, 0.0f, 0.0f) },//�E����
		{XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f),	XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f) },//������
	};


	//�C���f�b�N�X���
	int index[] = { 0,1,2, 0,2,3, //�O��
					4,6,7, 4,7,5, //���
					1,8,2, 2,8,9, //�E����
					10,11,13, 10,13,12, //������
					14,16,15, 14,17,16, //���
					18,19,20, 18,20,21, //����
	};

	SetIndNum(sizeof(index) / sizeof(index[0]));

	hr = MyCreateBuffer(vertices, sizeof(vertices) / sizeof(vertices[0]), index);
	if (FAILED(hr))
	{
		//�G���[����
		MessageBox(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return hr;
	}

	return S_OK;
}
