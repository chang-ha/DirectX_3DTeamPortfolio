#include "PreCompile.h"
#include "GameEngineAO.h"
#include <GFSDK_SSAO.h>


GameEngineAO GameEngineAO::MainHBAO;

GameEngineAO::GameEngineAO() 
{
}

GameEngineAO::~GameEngineAO()
{
	if (nullptr != AOContext)
	{
		AOContext->Release();
		AOContext = nullptr;
	}
}

void GameEngineAO::Init(ID3D11Device* pDevice)
{
	GFSDK_SSAO_CustomHeap CustomHeap;
	CustomHeap.new_ = ::operator new;
	CustomHeap.delete_ = ::operator delete;

	GFSDK_SSAO_Status status;
	
	status = GFSDK_SSAO_CreateContext_D3D11(pDevice, &AOContext, &CustomHeap);
	assert(status == GFSDK_SSAO_OK); // HBAO+ requires feature level 11_0 or above
}

