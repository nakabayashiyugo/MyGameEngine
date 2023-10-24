#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wincodec.h>
#include "string"
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")
#pragma comment(lib, "WindowsCodecs.lib" )

using namespace DirectX;
//using namespace Microsoft::WRL;
using std::string;

class Texture
{
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
	XMFLOAT3 size_;
public:
	Texture();
	~Texture();
	HRESULT Load(std::string fileName);
	void Release();
	ID3D11SamplerState* GetSampler();
	ID3D11ShaderResourceView* GetSRV();
	XMFLOAT3 GetSize() { return size_; };
};