#include "PreCompile.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineGeometryShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineBlend.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineRenderTarget.h"

GameEngineMaterial::GameEngineMaterial()
{
	RasterizerPtr = GameEngineRasterizer::Find("EngineRasterizer");
	BlendStatePtr = GameEngineBlend::Find("AlphaBlend");;
	DepthStencilPtr = GameEngineDepthStencil::Find("EngineDepth");;
}

GameEngineMaterial::~GameEngineMaterial()
{
}

void GameEngineMaterial::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}

	VertexShaderPtr->Setting();
}

void GameEngineMaterial::GeometryShader()
{
	if (nullptr == GeometryShaderPtr)
	{
		// 지오메트리는 필수단계가 아니기 때문에 리턴만 하겠습니다.
		return;
		// MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}

	GeometryShaderPtr->Setting();
}

void GameEngineMaterial::GeometryShaderReset()
{
	if (nullptr == GeometryShaderPtr)
	{
		return;
	}

	GeometryShaderPtr->Reset();
}

void GameEngineMaterial::Rasterizer()
{
	if (nullptr == RasterizerPtr)
	{
		MsgBoxAssert("존재하지 않는 레스터 라이저를 세팅하려고 했습니다.");
	}

	RasterizerPtr->Setting();
}

void GameEngineMaterial::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 레스터 라이저를 세팅하려고 했습니다.");
	}

	PixelShaderPtr->Setting();
}

void GameEngineMaterial::Blend()
{
	if (nullptr == BlendStatePtr)
	{
		MsgBoxAssert("존재하지 않는 레스터 라이저를 세팅하려고 했습니다.");
	}

	BlendStatePtr->Setting();
}

void GameEngineMaterial::DepthStencil()
{
	if (false == GameEngineRenderTarget::IsDepth)
	{
		GameEngineCore::GetContext()->OMSetDepthStencilState(nullptr, 0);
		return;
	}

	if (nullptr == DepthStencilPtr)
	{
		MsgBoxAssert("존재하지 않는 깊이 체크 세팅을 세팅하려고 했습니다.");
	}

	DepthStencilPtr->Setting();
}

void GameEngineMaterial::SetVertexShader(std::string_view _Value) 
{
	VertexShaderPtr = GameEngineVertexShader::Find(_Value);

	if (nullptr == VertexShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}
}

void GameEngineMaterial::SetGeometryShader(std::string_view _Value)
{
	GeometryShaderPtr = GameEngineGeometryShader::Find(_Value);

	if (nullptr == GeometryShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 지오메트리쉐이더를 세팅하려고 했습니다.");
	}
}

void GameEngineMaterial::SetRasterizer(std::string_view _Value) 
{
	RasterizerPtr = GameEngineRasterizer::Find(_Value);

	if (nullptr == RasterizerPtr)
	{
		MsgBoxAssert("존재하지 않는 레스터 라이저를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineMaterial::SetPixelShader(std::string_view _Value) 
{
	PixelShaderPtr = GameEnginePixelShader::Find(_Value);

	if (nullptr == PixelShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 픽셀쉐이더를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineMaterial::SetBlendState(std::string_view _Value) 
{
	BlendStatePtr = GameEngineBlend::Find(_Value);

	if (nullptr == BlendStatePtr)
	{
		MsgBoxAssert("존재하지 않는 블랜드를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineMaterial::SetDepthState(std::string_view _Value)
{
	DepthStencilPtr = GameEngineDepthStencil::Find(_Value);

	if (nullptr == DepthStencilPtr)
	{
		MsgBoxAssert("존재하지 않는 깊이버퍼 세팅을 사용하려고 했습니다.");
		return;
	}
}