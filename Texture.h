#pragma once
#include <d3d11.h>
#include "string"
#include <wrl.h>

using namespace Microsoft::WRL;
using std::string;

class Texture
{
public:
	Texture();
	~Texture();
	HRESULT Load(std::string fileName);
	void Release();
};