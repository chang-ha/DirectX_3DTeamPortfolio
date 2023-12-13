#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineTransform.h"

#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineSampler.h"
#include "GameEngineVertexShader.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSprite.h"
#include "GameEngineBlend.h"
#include "GameEngineMesh.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineMaterial.h"
#include "GameEngineFont.h"
#include "GAMEENGINERENDERTARGET.H"

void GameEngineDevice::ResourcesInit()
{
	GameEngineFont::Load("돋움");

	{
		// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("GameEngineResources");
		Dir.MoveChild("Textrure");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateSingle("NSet.png");
	}

	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(1);

		Vertex[0] = { { 0.0f, 0.0f, 0.0f, 1.0f } };

		GameEngineVertexBuffer::Create("PointMesh", Vertex);

		std::vector<unsigned int> Index =
		{
			0
		};
		GameEngineIndexBuffer::Create("PointMesh", Index);

		std::shared_ptr<GameEngineMesh> PointMesh = GameEngineMesh::Create("PointMesh");
		PointMesh->SetTOPOLOGY(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	}

	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(2);

		Vertex[0] = { { 1.0f, 0.0f, 0.0f, 1.0f } };
		Vertex[1] = { { 0.0f, 0.0f, 0.0f, 1.0f } };

		GameEngineVertexBuffer::Create("Line", Vertex);

		std::vector<unsigned int> Index =
		{
			0, 1
		};
		GameEngineIndexBuffer::Create("Line", Index);

		std::shared_ptr<GameEngineMesh> LineMesh = GameEngineMesh::Create("Line");
		LineMesh->SetTOPOLOGY(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		// LineMesh->SetTOPOLOGY(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(4 * 6);

		GameEngineVertex BaseVertexs[4];

		BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		// 앞면
		Vertex[0] = BaseVertexs[0];
		Vertex[1] = BaseVertexs[1];
		Vertex[2] = BaseVertexs[2];
		Vertex[3] = BaseVertexs[3];

		// 뒷면
		Vertex[4].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 180.0f);
		Vertex[5].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 180.0f);
		Vertex[6].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 180.0f);
		Vertex[7].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 180.0f);

		// 왼쪽이나 오른쪽
		Vertex[8].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, 90.0f);
		Vertex[9].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, 90.0f);
		Vertex[10].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, 90.0f);
		Vertex[11].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, 90.0f);

		// 왼쪽이나 오른쪽
		Vertex[12].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, -90.0f);
		Vertex[13].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, -90.0f);
		Vertex[14].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, -90.0f);
		Vertex[15].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, -90.0f);

		// 위거나 아래
		Vertex[16].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 90.0f);
		Vertex[17].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 90.0f);
		Vertex[18].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 90.0f);
		Vertex[19].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 90.0f);

		Vertex[20].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, -90.0f);
		Vertex[21].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, -90.0f);
		Vertex[22].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, -90.0f);
		Vertex[23].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, -90.0f);

		GameEngineVertexBuffer::Create("Box", Vertex);
	}


	// Sphere
		// 스피어
	{
		GameEngineVertex V;
		std::vector<GameEngineVertex> VBVector;
		std::vector<UINT> IBVector;

		float Radius = 0.5f;
		// 북극점부터 시작합니다.
		V.POSITION = float4(0.0f, Radius, 0.0f, 1.0f);
		V.TEXCOORD = float4(0.5f, 0.0f);
		// 노말 백터 혹은 법선백터라고 불리며
		// 면에 수직인 벡터를 의미하게 된다.
		// 빛을 반사할때 필수.
		V.NORMAL = float4(0.0f, Radius, 0.0f, 1.0f);
		V.NORMAL.Normalize();
		V.NORMAL.W = 0.0f;
		V.TANGENT = float4(1.0f, 0.0f, 0.0f, 0.0f);
		V.BINORMAL = float4(0.0f, 0.0f, 1.0f, 0.0f);

		VBVector.push_back(V);

		UINT iStackCount = 16; // 가로 분할 개수입니다.
		UINT iSliceCount = 16; // 세로분할 개수

		float yRotAngle = GameEngineMath::PI / (float)iStackCount;
		float zRotAngle = (GameEngineMath::PI * 2) / (float)iSliceCount;

		// UV의 가로세로 간격값을 구한다.
		float yUvRatio = 1.0f / (float)iStackCount;
		float zUvRatio = 1.0f / (float)iStackCount;

		for (UINT y = 1; y < iStackCount; ++y)
		{
			// 각 간격에 대한 각도값
			float phi = y * yRotAngle;
			for (UINT z = 0; z < iSliceCount + 1; ++z)
			{
				float theta = z * zRotAngle;
				V.POSITION = float4{
					Radius * sinf(y * yRotAngle) * cosf(z * zRotAngle),
					Radius * cosf(y * yRotAngle),
					Radius * sinf(y * yRotAngle) * sinf(z * zRotAngle),
					1.0f // 위치 크기 값에 영향을 주기 위해서
				};

				// V.Pos *= GameEngineRandom::RandomFloat(-0.9f, 0.1f);

				V.TEXCOORD = float4(yUvRatio * z, zUvRatio * y);
				V.NORMAL = V.POSITION.NormalizeReturn();
				V.NORMAL.W = 0.0f;

				V.TANGENT.X = -Radius * sinf(phi) * sinf(theta);
				V.TANGENT.Y = 0.0f;
				V.TANGENT.Z = Radius * sinf(phi) * cosf(theta);
				V.TANGENT = V.TANGENT.NormalizeReturn();
				V.TANGENT.W = 0.0f;

				V.BINORMAL = float4::Cross3D(V.TANGENT, V.NORMAL);
				V.BINORMAL = V.BINORMAL.NormalizeReturn();
				V.BINORMAL.W = 0.0f;


				VBVector.push_back(V);
			}
		}

		// 남극점
		V.POSITION = float4(0.0f, -Radius, 0.0f, 1.0f);
		V.TEXCOORD = float4(0.5f, 1.0f);
		V.NORMAL = float4(0.0f, -Radius, 0.0f, 1.0f);
		V.NORMAL.Normalize();
		V.NORMAL.W = 0.0f;
		V.TANGENT = float4(-1.0f, 0.0f, 0.0f, 0.0f);
		V.BINORMAL = float4(0.0f, 0.0f, -1.0f, 0.0f);
		VBVector.push_back(V);

		// 인덱스 버퍼를 만듭니다.
		IBVector.clear();

		// 북극점을 이루는 점을 만드는건.
		for (UINT i = 0; i < iSliceCount; i++)
		{
			// 시작은 무조건 북극점
			IBVector.push_back(0);
			IBVector.push_back(i + 2);
			IBVector.push_back(i + 1);
		}

		for (UINT y = 0; y < iStackCount - 2; y++)
		{
			for (UINT z = 0; z < iSliceCount; z++)
			{
				IBVector.push_back((iSliceCount + 1) * y + z + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + z + 1);

				IBVector.push_back((iSliceCount + 1) * y + z + 1);
				IBVector.push_back((iSliceCount + 1) * y + (z + 1) + 1);
				IBVector.push_back((iSliceCount + 1) * (y + 1) + (z + 1) + 1);

			}
		}

		// 마지막으로 남극점 인덱스
		UINT iBotIndex = (UINT)VBVector.size() - 1;
		for (UINT i = 0; i < iSliceCount; i++)
		{
			// 시작은 무조건 북극점
			IBVector.push_back(iBotIndex);
			IBVector.push_back(iBotIndex - (i + 2));
			IBVector.push_back(iBotIndex - (i + 1));
		}

		GameEngineVertexBuffer::Create("Sphere", VBVector);
		GameEngineIndexBuffer::Create("Sphere", IBVector);

		GameEngineMesh::Create("Sphere");

		std::shared_ptr<GameEngineMesh> Mesh = GameEngineMesh::Create("DebugSphere", "Sphere", "Sphere");
	}


	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(4);

		// 이미지를 자르려면 TEXCOORD값이 바뀌어야 하는데.
		Vertex[0] = { { -0.5f, 0.5f, 0.0f, 1.0f }, {0.0f, 0.0f} };
		Vertex[1] = { { 0.5f, 0.5f, 0.0f, 1.0f } , {1.0f, 0.0f} };
		Vertex[2] = { { 0.5f, -0.5f, 0.0f, 1.0f }  , {1.0f, 1.0f} };
		Vertex[3] = { { -0.5f, -0.5f, 0.0f, 1.0f } , {0.0f, 1.0f} };

		GameEngineVertexBuffer::Create("Rect", Vertex);


		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};

		GameEngineIndexBuffer::Create("Rect", Index);

		GameEngineMesh::Create("Rect");
	}



	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(4);

		Vertex[0] = { { -1.0f, 1.0f, 0.0f, 1.0f },  {0.0f, 0.0f} };
		Vertex[1] = { { 1.0f, 1.0f, 0.0f, 1.0f } , {1.0f, 0.0f} };
		Vertex[2] = { { 1.0f, -1.0f, 0.0f, 1.0f }  , {1.0f, 1.0f} };
		Vertex[3] = { { -1.0f, -1.0f, 0.0f, 1.0f } , {0.0f, 1.0f} };

		GameEngineVertexBuffer::Create("FullRect", Vertex);


		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};

		GameEngineIndexBuffer::Create("FullRect", Index);

		GameEngineMesh::Create("FullRect");
	}

	{

		//D3D11_FILL_MODE FillMode;
		// 랜더링 할때 채우기 모드를 결정한다.
		
		// 외적했는데 z방향이 어디냐?
		// D3D11_CULL_NONE => 방향이 어디든 건져낸다.
		// D3D11_CULL_BACK => z가 앞쪽인 픽셀들은 안건져 낸다.
		// D3D11_CULL_FRONT => z가 뒤쪽인 픽셀들은 안건져 낸다.
		// 
		// 0, 1, 2,
		// 0, 2, 3
		// 인덱스 버퍼의 그리는 순서와 연관이 크다.

		// 이녀석은 인덱스 버퍼

		//D3D11_CULL_MODE CullMode;
		//BOOL FrontCounterClockwise;
		//INT DepthBias;
		//FLOAT DepthBiasClamp;
		//FLOAT SlopeScaledDepthBias;
		//BOOL DepthClipEnable;
		//BOOL ScissorEnable;
		//BOOL MultisampleEnable;
		//BOOL AntialiasedLineEnable;

		D3D11_RASTERIZER_DESC Desc = {};
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		// Desc.DepthClipEnable = TRUE;
		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Create("EngineRasterizer", Desc);
	}

	{
		// 이걸 세팅하는 순간
		// order가 2d랜더링의 순서가 되는것이 아니라
		// z의 값이 순서를 결정하게 되기 때문에
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		//BOOL DepthEnable;
		//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
		//D3D11_COMPARISON_FUNC DepthFunc;
		//BOOL StencilEnable;
		//UINT8 StencilReadMask;
		//UINT8 StencilWriteMask;
		//D3D11_DEPTH_STENCILOP_DESC FrontFace;
		//D3D11_DEPTH_STENCILOP_DESC BackFace;

		Desc.DepthEnable = true;
		// 깊이 테스트만 하고 안쓸수도 있다.
		// Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		Desc.StencilEnable = false;
		std::shared_ptr<GameEngineDepthStencil> Rasterizer = GameEngineDepthStencil::Create("EngineDepth", Desc);
	}


	{
		// 이걸 세팅하는 순간
		// order가 2d랜더링의 순서가 되는것이 아니라
		// z의 값이 순서를 결정하게 되기 때문에
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		//BOOL DepthEnable;
		//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
		//D3D11_COMPARISON_FUNC DepthFunc;
		//BOOL StencilEnable;
		//UINT8 StencilReadMask;
		//UINT8 StencilWriteMask;
		//D3D11_DEPTH_STENCILOP_DESC FrontFace;
		//D3D11_DEPTH_STENCILOP_DESC BackFace;

		Desc.DepthEnable = true;
		// 깊이 테스트만 하고 안쓸수도 있다.
		// Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.StencilEnable = false;
		std::shared_ptr<GameEngineDepthStencil> Rasterizer = GameEngineDepthStencil::Create("AlwaysDepth", Desc);
	}


	{

		//D3D11_FILL_MODE FillMode;
		// 랜더링 할때 채우기 모드를 결정한다.

		// 외적했는데 z방향이 어디냐?
		// D3D11_CULL_NONE => 방향이 어디든 건져낸다.
		// D3D11_CULL_BACK => z가 앞쪽인 픽셀들은 안건져 낸다.
		// D3D11_CULL_FRONT => z가 뒤쪽인 픽셀들은 안건져 낸다.
		// 
		// 0, 1, 2,
		// 0, 2, 3
		// 인덱스 버퍼의 그리는 순서와 연관이 크다.

		// 이녀석은 인덱스 버퍼

		//D3D11_CULL_MODE CullMode;
		//BOOL FrontCounterClockwise;
		//INT DepthBias;
		//FLOAT DepthBiasClamp;
		//FLOAT SlopeScaledDepthBias;
		//BOOL DepthClipEnable;
		//BOOL ScissorEnable;
		//BOOL MultisampleEnable;
		//BOOL AntialiasedLineEnable;

		D3D11_RASTERIZER_DESC Desc = {};
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		// Desc.DepthClipEnable = TRUE;
		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Create("EngineWireRasterizer", Desc);
	}


	{
		D3D11_BLEND_DESC Desc = {};

		// 이건 좀 느린데.
		// 깊이버퍼라는 것과 관련이 있습니다.
		// 나중에 함
		// Desc.AlphaToCoverageEnable

		// 랜더타겟을 세팅하는것과 관련이 있는데.
		// 랜더타겟은 한번에 8개를 세팅할수 있다.
		// 그걸 1개 이상을 세팅했을때 각기 다른 세팅을 니가 일일이 넣어줄거냐 라는 옵션입니다.
		// 안한다하면 0번째걸로 나머지 모두를 세팅한다.
		Desc.IndependentBlendEnable = false;

		// 블랜드 켤거냐.
		Desc.RenderTarget[0].BlendEnable = true;

		// 색깔 전체를 대상으로 삼겠다.
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// + 빼고 써본적이 없어요.
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		// https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/ne-d3d11-d3d11_blend
		
		// src srcColor * src의 알파
		// 1, 0, 0(, 1) * 1.0f
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src팩터

		// src 1, 0, 0, 1 * (1 - src의 알파)
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		// 
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("AlphaBlend", Desc);
	}


	{

		D3D11_SAMPLER_DESC Desc = {};
		// 일반적인 보간형식 <= 뭉개진다.
		// D3D11_FILTER_MIN_MAG_MIP_
		// 그 밉맵에서 색상가져올때 다 뭉개는 방식으로 가져오겠다.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Rasterizer = GameEngineSampler::Create("EngineBaseSampler", Desc);
	}

	{

		D3D11_SAMPLER_DESC Desc = {};
		// 일반적인 보간형식 <= 뭉개진다.
		// D3D11_FILTER_MIN_MAG_MIP_
		// 그 밉맵에서 색상가져올때 다 뭉개는 방식으로 가져오겠다.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Sampler = GameEngineSampler::Create("EngineBaseWRAPSampler", Desc);
	}


	{

		D3D11_SAMPLER_DESC Desc = {};
		// 일반적인 보간형식 <= 뭉개진다.
		// D3D11_FILTER_MIN_MAG_MIP_
		// 그 밉맵에서 색상가져올때 다 뭉개는 방식으로 가져오겠다.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Rasterizer = GameEngineSampler::Create("POINT", Desc);
	}

	{

		D3D11_SAMPLER_DESC Desc = {};
		// 일반적인 보간형식 <= 뭉개진다.
		// D3D11_FILTER_MIN_MAG_MIP_
		// 그 밉맵에서 색상가져올때 다 뭉개는 방식으로 가져오겠다.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Rasterizer = GameEngineSampler::Create("LINEAR", Desc);
	}



	{
		// 엔진용 쉐이더를 전부다 전부다 로드하는 코드를 친다.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineCoreShader");
		Dir.MoveChild("GameEngineCoreShader");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
			GameEngineFile& File = Files[i];
			GameEngineShader::AutoCompile(File);
		}
	}


	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DTexture");
		Mat->SetVertexShader("TextureShader_VS");
		Mat->SetPixelShader("TextureShader_PS");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DTextureWire");
		Mat->SetVertexShader("DebugColor_VS");
		Mat->SetPixelShader("DebugColor_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineWireRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DDebugLine");
		Mat->SetVertexShader("DebugLine_VS");
		Mat->SetPixelShader("DebugLine_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("TargetMerge");
		Mat->SetVertexShader("TargetMerge_VS");
		Mat->SetPixelShader("TargetMerge_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FadePostEffect");
		Mat->SetVertexShader("FadePostEffect_VS");
		Mat->SetPixelShader("FadePostEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("BlurPostEffect");
		Mat->SetVertexShader("BlurPostEffect_VS");
		Mat->SetPixelShader("BlurPostEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("ParticleRender");
		Mat->SetVertexShader("ParticleRender_VS");
		Mat->SetGeometryShader("ParticleRender_GS");
		Mat->SetPixelShader("ParticleRender_PS");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FBXColor");
		Mat->SetVertexShader("FBXColorShader_VS");
		Mat->SetPixelShader("FBXColorShader_PS");
	}



	GameEngineRenderTarget::MergeRenderUnitInit();
}