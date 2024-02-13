#include "PreCompile.h"
#include "ContentResources.h"
#include <GameEngineCore/GameEngineBlend.h>

#include "Monster_LothricKn.h"
#include "LUTEffect.h"

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
	
	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FBX_Static_NorX_SpcX");
		Mat->SetVertexShader("ContentsStaticMesh_NorX_SpcX_VS");
		Mat->SetPixelShader("ContentsStaticMesh_NorX_SpcX_PS");
	}
	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FBX_Static_SpcX");
		Mat->SetVertexShader("ContentsStaticMesh_SpcX_VS");
		Mat->SetPixelShader("ContentsStaticMesh_SpcX_PS");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FBX_Static_Color");
		Mat->SetVertexShader("ContentsStaticMesh_Color_VS");
		Mat->SetPixelShader("ContentsStaticMesh_Color_PS");
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


	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FXAA");

		Mat->SetVertexShader("FXAA_VS");
		Mat->SetPixelShader("FXAA_PS");
		Mat->SetRasterizer("EngineRasterizer");
		Mat->SetBlendState("MergeBlend");
		Mat->SetDepthState("AlwaysDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("BloomBlur");

		Mat->SetVertexShader("BloomBlur_VS");
		Mat->SetPixelShader("BloomBlur_PS");
		//Mat->SetRasterizer("EngineRasterizer");
		//Mat->SetBlendState("MergeBlend");
		//Mat->SetDepthState("AlwaysDepth");
	}
	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("BloomBright");

		Mat->SetVertexShader("BloomBright_VS");
		Mat->SetPixelShader("BloomBright_PS");
		//Mat->SetRasterizer("EngineRasterizer");
		//Mat->SetBlendState("MergeBlend");
		//Mat->SetDepthState("AlwaysDepth");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("BloomCombine");

		Mat->SetVertexShader("BloomCombine_VS");
		Mat->SetPixelShader("BloomCombine_PS");
		//Mat->SetRasterizer("EngineRasterizer");
		//Mat->SetBlendState("MergeBlend");
		//Mat->SetDepthState("AlwaysDepth");
	}

	// LUT
	{
		LUTEffect::Load();

		
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("LUT");

		Mat->SetVertexShader("LUT_VS");
		Mat->SetPixelShader("LUT_PS");
		Mat->SetRasterizer("EngineRasterizer");
		Mat->SetBlendState("MergeBlend");
		Mat->SetDepthState("AlwaysDepth");
	}


	BaseActor::LoadEvent(static_cast<int>(Enum_ActorType::LothricKn));
	BaseActor::LoadEvent(static_cast<int>(Enum_ActorType::Boss_Vordt));

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