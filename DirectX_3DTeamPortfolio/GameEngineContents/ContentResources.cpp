#include "PreCompile.h"
#include "ContentResources.h"
#include <GameEngineCore/GameEngineBlend.h>

#include "Monster_LothricKn.h"

ContentResources::ContentResources()
{

}

ContentResources::~ContentResources()
{

}

void ContentResources::ContentResourcesInit()
{
	{
		{
			// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("GameEngineContentsShader");
			std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineShader::AutoCompile(File);
			}
		}
	}

	{
		{
			// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Mesh");
			std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fbx" }, true);

			for (size_t i = 0; i < Files.size(); i++)
			{
				std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Files[i].GetStringPath());
			}
		}
	}

	{
		// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Mesh");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fbx" }, true);

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineFBXAnimation> Mesh = GameEngineFBXAnimation::Load(Files[i].GetStringPath());
		}
	}

	{
		{
			// 분할된 자체포맷 첫번째 로드
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Mesh");
			std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".FBX0" }, true);

			for (size_t i = 0; i < Files.size(); i++)
			{
				std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(Files[i].GetStringPath());
			}
		}
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FBX_Animation");
		Mat->SetVertexShader("ContentsAnimationMesh_VS");
		Mat->SetPixelShader("ContentsAnimationMesh_PS");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FBX_Static");
		Mat->SetVertexShader("ContentsStaticMesh_VS");
		Mat->SetPixelShader("ContentsStaticMesh_PS");
	}

	//PostEffect

	{
		D3D11_BLEND_DESC Desc = { 0, };

		Desc.AlphaToCoverageEnable = false;
		Desc.IndependentBlendEnable = false;

		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		GameEngineBlend::Create("MergeBlend", Desc);
	}

	//{
	//	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FadePostEffect");
	//	Mat->SetVertexShader("FadePostEffect_VS");
	//	Mat->SetPixelShader("FadePostEffect_PS");
	//	Mat->SetDepthState("AlwaysDepth");
	//	Mat->SetRasterizer("EngineRasterizer");
	//}

	//{
	//	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("BlurPostEffect");
	//	Mat->SetVertexShader("BlurPostEffect_VS");
	//	Mat->SetPixelShader("BlurPostEffect_PS");
	//	Mat->SetDepthState("AlwaysDepth");
	//	Mat->SetRasterizer("EngineRasterizer");
	//}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FXAA");

		Mat->SetVertexShader("FXAA_VS");
		Mat->SetPixelShader("FXAA_PS");
		Mat->SetRasterizer("EngineRasterizer");
		Mat->SetBlendState("MergeBlend");
		Mat->SetDepthState("AlwaysDepth");
	}


	BaseMonster::LoadEvent(static_cast<int>(Monster_LothricKn::Type));

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("TestSoundFile");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile pFile : Files)
		{
			GameEngineSound::SoundLoad(pFile.GetStringPath());
		}
	}

	//Defferd



	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("ContentsDeferredLightRender");
		Mat->SetVertexShader("ContentsDeferredLightRender_VS");
		Mat->SetPixelShader("ContentsDeferredLightRender_PS");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("ContentsDeferredMergeRender");
		Mat->SetVertexShader("ContentsDeferredMergeRender_VS");
		Mat->SetPixelShader("ContentsDeferredMergeRender_PS");
	}
}