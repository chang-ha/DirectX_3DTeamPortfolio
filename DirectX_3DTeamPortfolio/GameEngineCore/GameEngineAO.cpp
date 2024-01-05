#include "PreCompile.h"
#include "GameEngineAO.h"
#include <GFSDK_SSAO.h>

GameEngineAO::GameEngineAO() 
{
}

GameEngineAO::~GameEngineAO()
{
}

void GameEngineAO::Init(ID3D11Device* pDevice)
{
	GFSDK_SSAO_CustomHeap CustomHeap;
	CustomHeap.new_ = ::operator new;
	CustomHeap.delete_ = ::operator delete;

	GFSDK_SSAO_Status status;
	GFSDK_SSAO_Context_D3D11* pAOContext;
	status = GFSDK_SSAO_CreateContext_D3D11(pDevice, &pAOContext, &CustomHeap);
	assert(status == GFSDK_SSAO_OK); // HBAO+ requires feature level 11_0 or above
}

