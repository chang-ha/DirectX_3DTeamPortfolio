#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineCore.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

const GameEngineColor GameEngineColor::RED = { 255, 0, 0, 255 };
const GameEngineColor GameEngineColor::GREEN = { 0, 255, 0, 255 };
const GameEngineColor GameEngineColor::BLUE = { 0, 0, 255, 255 };
const GameEngineColor GameEngineColor::MAGENTA = { 255, 0, 255, 255 };
const GameEngineColor GameEngineColor::YELLOW = { 255, 255, 0, 255 };
const GameEngineColor GameEngineColor::AQUA = { 0, 255, 255, 255 };
const GameEngineColor GameEngineColor::BLACK = { 0, 0, 0, 255 };
const GameEngineColor GameEngineColor::WHITE = { 255, 255, 255, 255 };

GameEngineTexture::GameEngineTexture() 
{
}

GameEngineTexture::~GameEngineTexture() 
{
	if (nullptr != DSV)
	{
		DSV->Release();
		DSV = nullptr;
	}

	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}

	if (nullptr != RTV)
	{
		RTV->Release();
		RTV = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
	}
}


void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RTV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 랜더타겟뷰를 생성하려고 했습니다.");
		return;
	}

	// 이미지를 수정할수 있는 권한을 '만든다'

	HRESULT Result = GameEngineCore::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("랜더타겟뷰 생성에 실패했습니다.");
		return;
	}

}

// 쉐이더 세팅용
void GameEngineTexture::CreateShaderResourceView()
{
	if (nullptr != SRV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 쉐이더 리소스 뷰 생성하려고 했습니다.");
		return;
	}

	// 이미지를 수정할수 있는 권한을 '만든다'

	HRESULT Result = GameEngineCore::GetDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	if (S_OK != Result)
	{
		MsgBoxAssert("쉐이더 리소스 뷰 생성에 실패했습니다.");
		return;
	}

}

// 깊버거 세팅용
void GameEngineTexture::CreateDepthStencilView()
{
	if (nullptr != DSV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 쉐이더 리소스 뷰 생성하려고 했습니다.");
		return;
	}

	// 이미지를 수정할수 있는 권한을 '만든다'

	HRESULT Result = GameEngineCore::GetDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);

	if (S_OK != Result)
	{
		MsgBoxAssert("쉐이더 리소스 뷰 생성에 실패했습니다.");
		return;
	}
}

void GameEngineTexture::ResLoad(std::string_view _Path)
{
	// 팩토리니 어뎁터니 

	// png 및 다수의 이미지를 로드 가능한 함수 

	GameEnginePath NewPath = _Path;

	std::string Ext = GameEngineString::ToUpperReturn(NewPath.GetExtension());

	std::wstring wPath = GameEngineString::AnsiToUnicode(_Path);

	// 그래픽 
	if (Ext == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
		}
	}
	else if (Ext == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
		}
		
	}
	else if(S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
	}

	// 로드의 목적은 쉐이더 세팅 권한을 얻어오는것이 최종적인 목적인것이다
	// 이것도 라이브러리 함수
	if (S_OK != DirectX::CreateShaderResourceView
	(
		GameEngineCore::GetDevice(),
		Image.GetImages(),
		Image.GetImageCount(), // 이미지가 겹쳐있을수 있다.
		Image.GetMetadata(),
		&SRV
	))
	{
		MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
	}

	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);
}

void GameEngineTexture::VSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::PSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::CSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->CSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::VSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* ResetRes = nullptr;
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &ResetRes);
}
void GameEngineTexture::PSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* ResetRes = nullptr;
	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &ResetRes);
}

void GameEngineTexture::CSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* ResetRes = nullptr;
	GameEngineCore::GetContext()->CSSetShaderResources(_Slot, 1, &ResetRes);
}

void GameEngineTexture::ResCreate(ID3D11Texture2D* _Res)
{
	Texture2D = _Res;

	Texture2D->GetDesc(&Desc);

	CreateRenderTargetView();

	int a = 0;
}

void GameEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Desc) 
{
	Desc = _Desc;

	if (S_OK != GameEngineCore::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D))
	{
		MsgBoxAssert("if (S_OK != GameEngineCore::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D))");
	}

	if (D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET & Desc.BindFlags)
	{
		CreateRenderTargetView();
	}

	if (D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE & Desc.BindFlags)
	{
		CreateShaderResourceView();
	}

	if (D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL & Desc.BindFlags)
	{
		CreateDepthStencilView();
	}
}

GameEngineColor GameEngineTexture::GetColor(unsigned int _X, unsigned int _Y, GameEngineColor _DefaultColor)
{

	if (0 > _X)
	{
		return _DefaultColor;
	}

	if (0 > _Y)
	{
		return _DefaultColor;
	}

	if (_X >= GetScale().uiX())
	{
		return _DefaultColor;
	}

	if (_Y >= GetScale().uiY())
	{
		return _DefaultColor;
	}

	DXGI_FORMAT Fmt = Image.GetMetadata().format;


	// 첫번째 주소를 1바이트 자료형으로 줬다.
	unsigned char* Ptr = Image.GetPixels();

	switch (Fmt)
	{
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	{
		GameEngineColor ResultColor;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4;
		ResultColor.B = Ptr[0];
		ResultColor.G = Ptr[1];
		ResultColor.R = Ptr[2];
		ResultColor.A = Ptr[3];
		return ResultColor;
	}
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	{
		GameEngineColor ResultColor;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4;
		ResultColor.R = Ptr[0];
		ResultColor.G = Ptr[1];
		ResultColor.B = Ptr[2];
		ResultColor.A = Ptr[3];
		return ResultColor;
	}
	default:
		MsgBoxAssert("색깔을 처리하는 함수를 만들지 없는 포맷입니다");
		break;
	}


	return _DefaultColor;
}
