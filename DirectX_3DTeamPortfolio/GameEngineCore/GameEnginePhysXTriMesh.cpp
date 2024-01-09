#include "PreCompile.h"
#include "GameEnginePhysXTriMesh.h"
#include "GameEnginePhysXLevel.h"

GameEnginePhysXTriMesh::GameEnginePhysXTriMesh()
{

}

GameEnginePhysXTriMesh::~GameEnginePhysXTriMesh()
{

}
void GameEnginePhysXTriMesh::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void GameEnginePhysXTriMesh::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void GameEnginePhysXTriMesh::Start()
{
	GameEnginePhysXComponent::Start();
	ParentActor = GetActor();
}

void GameEnginePhysXTriMesh::Update(float _Delta)
{
	
}

void GameEnginePhysXTriMesh::Release()
{
	if (nullptr != StaticActor)
	{
		StaticActor->release();
		StaticActor = nullptr;
	}
}

void GameEnginePhysXTriMesh::PhysXComponentInit(std::string_view _MeshName, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	MeshPath;

	GameEnginePath FilePath = GameEnginePath(_MeshName);
	FilePath.ChangeExtension("PhysXTriMesh");
	std::string FimeName = FilePath.GetFileName();
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("PhysXSerialization");
	FilePath.MoveChild("PhysXSerialization");
	MeshPath = GameEnginePath(FilePath.GetStringPath() + "\\" + FimeName);
	
	if (true == MeshPath.IsExits())
	{
		PhysXReadSerialization();
		return;
	}

	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Find(_MeshName);
	std::vector<FbxRenderUnitInfo> RenderUnitInfos = Mesh->GetRenderUnitInfos();

	if (0 == RenderUnitInfos.size())
	{
		MsgBoxAssert("로드되지 않은 Mesh로 삼각형 매쉬를 만들 수 없습니다.");
		return;
	}

	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldQuat = Transform.GetWorldRotationEuler().EulerDegToQuaternion();

	physx::PxVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);
	physx::PxTransform PxTransform(Pos, Quat);
	StaticActor = GameEnginePhysX::GetPhysics()->createRigidStatic(PxTransform);

	for (int i = 0; i < RenderUnitInfos.size(); i++)
	{
		FbxRenderUnitInfo& UnitInfo = RenderUnitInfos[i];
		std::vector<physx::PxVec3> Vertexs;
		std::vector<physx::PxVec3> Indexs;
		Vertexs.resize(UnitInfo.Vertexs.size());

		for (int i = 0; i < UnitInfo.Vertexs.size(); i++)
		{
			const float4 Position = UnitInfo.Vertexs[i].POSITION;
			Vertexs[i].x = Position.X;
			Vertexs[i].y = Position.Y;
			Vertexs[i].z = Position.Z;
		}

		physx::PxTriangleMeshDesc MeshDesc;
		MeshDesc.points.count = static_cast<physx::PxU32>(Vertexs.size());
		MeshDesc.points.stride = sizeof(physx::PxVec3);
		MeshDesc.points.data = &Vertexs[0];

		MeshDesc.triangles.count = static_cast<physx::PxU32>(UnitInfo.Indexs[0].size() / 3);
		MeshDesc.triangles.stride = 3 * sizeof(physx::PxU32);
		MeshDesc.triangles.data = &UnitInfo.Indexs[0][0];

		if (true == MeshDesc.isValid())
		{
			physx::PxDefaultMemoryOutputStream WriteBuffer;

			if (true == GameEnginePhysX::GetCooking()->cookTriangleMesh(MeshDesc, WriteBuffer))
			{
				physx::PxDefaultMemoryInputData ReadBuffer(WriteBuffer.getData(), WriteBuffer.getSize());
				physx::PxTriangleMesh* TriMesh = GameEnginePhysX::GetPhysics()->createTriangleMesh(ReadBuffer);
				physx::PxTriangleMeshGeometry Geom(TriMesh);
				physx::PxShape* TriMeshShape = GameEnginePhysX::GetPhysics()->createShape(Geom, *_Material);

				StaticActor->attachShape(*TriMeshShape);
			}
			else
			{
				MsgBoxAssert("TriMesh생성에 실패했습니다.");
				return;
			}
		}
		else
		{
			MsgBoxAssert("매쉬 정보가 잘못되었습니다.");
		}
	}

	Scene->addActor(*StaticActor);
	PhysXWriteSerialization();
}

void GameEnginePhysXTriMesh::PhysXWriteSerialization()
{
	physx::PxCooking* Cooking = GameEnginePhysX::GetCooking();

	physx::PxSerializationRegistry* Registry = physx::PxSerialization::createSerializationRegistry(*GameEnginePhysX::GetPhysics());

	// Create a collection and all objects for serialization
	physx::PxCollection* Collection = PxCreateCollection();
	Collection->add(*StaticActor);
	physx::PxSerialization::complete(*Collection, *Registry);

	// Serialize either to binary or RepX
	physx::PxDefaultFileOutputStream OutStream(MeshPath.GetStringPath().c_str());

	// Binary
	physx::PxSerialization::serializeCollectionToBinary(OutStream, *Collection, *Registry);
	//~Binary

	// RepX
	// physx::PxSerialization::serializeCollectionToXml(OutStream, *Collection, *Registry);
	Collection->release();
	Registry->release();
}

void GameEnginePhysXTriMesh::PhysXReadSerialization()
{
	physx::PxSerializationRegistry* Registry = physx::PxSerialization::createSerializationRegistry(*GameEnginePhysX::GetPhysics());

	// Binary
	// Open file and get file size
	 FILE* File;
	 errno_t Error = fopen_s(&File, MeshPath.GetStringPath().c_str(), "rb");
	 
	 if (Error != 0)
	 {
	 	MsgBoxAssert("파일 오픈에 문제가 있었습니다. 에러코드 : " + std::to_string(Error));
	 }
	 fseek(File, 0, SEEK_END);
	 unsigned fileSize = ftell(File);
	 fseek(File, 0, SEEK_SET);
	
	 // Allocate aligned memory, load data and deserialize
	 void* Data = malloc(fileSize + PX_SERIAL_FILE_ALIGN);
	 GameEnginePhysXLevel::AllData.push_back(Data);
	 void* Data128 = (void*)((size_t(Data) + PX_SERIAL_FILE_ALIGN) & ~(PX_SERIAL_FILE_ALIGN - 1));
	 fread(Data128, 1, fileSize, File);
	 fclose(File);
	 physx::PxCollection* Collection = physx::PxSerialization::createCollectionFromBinary(Data128, *Registry);
	//~Binary

	// RepX
	// Load file and deserialize collection - needs cooking library
	// physx::PxDefaultFileInputData InputData(MeshPath.GetStringPath().c_str());
	// physx::PxCollection* Collection = physx::PxSerialization::createCollectionFromXml(InputData, *GameEnginePhysX::GetCooking(), *Registry);
	//~RepX

	Scene->addCollection(*Collection);
	Collection->release();
	Registry->release();
}
