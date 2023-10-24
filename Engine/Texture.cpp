#include "Texture.h"
#include "Direct3D.h"
#include <DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

Texture::Texture()
	: pSampler_(nullptr), pSRV_(nullptr)
{
}

Texture::~Texture()
{
	Release();
}

HRESULT Texture::Load(std::string fileName)
{
	using namespace DirectX;
	////////////画像読み込み部分(変更)

	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());

	TexMetadata metadata;
	ScratchImage image;
	HRESULT hr;
	hr = LoadFromWICFile(wtext, WIC_FLAGS::WIC_FLAGS_NONE, &metadata, image);
	if (FAILED(hr))
	{
		return E_FAIL;
	}
	

	D3D11_SAMPLER_DESC  SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = Direct3D::pDevice_->CreateSamplerState(&SamDesc, &pSampler_);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	hr = CreateShaderResourceView(Direct3D::pDevice_, 
		image.GetImages(), image.GetImageCount(),metadata, & pSRV_);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// テクスチャを読み込む
	CoInitialize(NULL);
	IWICImagingFactory* pFactory = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pFormatConverter = NULL;
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&pFactory));
	hr = pFactory->CreateDecoderFromFilename(wtext, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
	if (FAILED(hr))
	{
		char message[256];
		wsprintf(message, "「%s」が見つかりまん", fileName.c_str());
		MessageBox(0, message, "画像ファイルの読み込みに失敗", MB_OK);
		return hr;
	}
	pDecoder->GetFrame(0, &pFrame);
	pFactory->CreateFormatConverter(&pFormatConverter);
	pFormatConverter->Initialize(pFrame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, NULL, 1.0f, WICBitmapPaletteTypeMedianCut);
	UINT imgWidth;
	UINT imgHeight;
	pFormatConverter->GetSize(&imgWidth, &imgHeight);
	size_ = XMFLOAT3((float)imgWidth, (float)imgHeight, 0);

	return S_OK;
}

void Texture::Release()
{
	SAFE_RELEASE(pSampler_);
	SAFE_RELEASE(pSRV_);
}

ID3D11SamplerState* Texture::GetSampler()
{
	return pSampler_;
}

ID3D11ShaderResourceView* Texture::GetSRV()
{
	return pSRV_;
}
