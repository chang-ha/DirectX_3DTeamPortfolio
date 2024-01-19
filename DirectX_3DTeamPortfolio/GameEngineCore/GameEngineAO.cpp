#include "PreCompile.h"
#include "GameEngineAO.h"
#include <GFSDK_SSAO.h>
//#include "GFSDK_SSAO.h"
#include "GameEngineRenderTarget.h"



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

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	HBAOTarget = GameEngineRenderTarget::Create();
	HBAOTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);

	GFSDK_SSAO_CustomHeap CustomHeap;
	CustomHeap.new_ = ::operator new;
	CustomHeap.delete_ = ::operator delete;

	


	GFSDK_SSAO_Status status;
	
	status = GFSDK_SSAO_CreateContext_D3D11(pDevice, &AOContext, &CustomHeap);
	assert(status == GFSDK_SSAO_OK); // HBAO+ requires feature level 11_0 or above
}

void GameEngineAO::DrawHBAO(std::shared_ptr<GameEngineRenderTarget> _RT, const TransformData& _Transform)
{
	GFSDK_SSAO_InputData_D3D11 Input;

	Input.DepthData.DepthTextureType = GFSDK_SSAO_HARDWARE_DEPTHS;
	Input.DepthData.pFullResDepthTextureSRV = _RT->GetDepthTexture()->GetSRV();
	Input.DepthData.ProjectionMatrix.Data = GFSDK_SSAO_Float4x4((CONST FLOAT*) & _Transform.ProjectionMatrix); // °Á ÀÌ³ð
	Input.DepthData.ProjectionMatrix.Layout = GFSDK_SSAO_ROW_MAJOR_ORDER;
	//Input.DepthData.MetersToViewSpaceUnits = 0.005f;





	GFSDK_SSAO_Output_D3D11 Output;
	Output.pRenderTargetView = HBAOTarget->GetTexture()->GetRTV();// m_pSceneRTs->ColorRTV; ¾Æ´Ô ÀÌ»õ³¢?
	Output.Blend.Mode = GFSDK_SSAO_OVERWRITE_RGB;

	GFSDK_SSAO_Parameters AOParams;
	AOParams.Radius = HBAOInfosValue.AORadius;
	AOParams.Bias = HBAOInfosValue.AOBias;
	AOParams.SmallScaleAO = HBAOInfosValue.SmallScaleAO;
	AOParams.LargeScaleAO = HBAOInfosValue.LargeScaleAO;
	AOParams.PowerExponent = HBAOInfosValue.PowerExponent;
	AOParams.Blur.Enable = HBAOInfosValue.BlurAO;
	AOParams.Blur.Sharpness = HBAOInfosValue.BlurSharpness;
	AOParams.Blur.Radius = GFSDK_SSAO_BLUR_RADIUS_4;

	GFSDK_SSAO_Status Status;

	if (nullptr == AOContext)
	{
		MsgBoxAssert("HBAO Init¼¼ÆÃÀ» ÇÏÁö ¾Ê¾Ò½À´Ï´Ù.");
		return;
	}
	

	Status = AOContext->RenderAO(GameEngineCore::GetContext(), Input, AOParams, Output);

	assert(Status == GFSDK_SSAO_OK);
}

