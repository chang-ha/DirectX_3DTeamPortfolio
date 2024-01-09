﻿#include "PreCompile.h"
#include "GameEnginePhysXTriMesh.h"


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
	MeshName = std::string(_MeshName);
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

		physx::PxTriangleMeshDesc meshDesc;
		meshDesc.points.count = static_cast<physx::PxU32>(Vertexs.size());
		meshDesc.points.stride = sizeof(physx::PxVec3);
		meshDesc.points.data = &Vertexs[0];

		meshDesc.triangles.count = static_cast<physx::PxU32>(UnitInfo.Indexs[0].size() / 3);
		meshDesc.triangles.stride = 3 * sizeof(physx::PxU32);
		meshDesc.triangles.data = &UnitInfo.Indexs[0][0];

		if (meshDesc.isValid())
		{
			physx::PxDefaultMemoryOutputStream writeBuffer;

			if (GameEnginePhysX::GetCooking()->cookTriangleMesh(meshDesc, writeBuffer))
			{
				physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
				physx::PxTriangleMesh* TriMesh = GameEnginePhysX::GetPhysics()->createTriangleMesh(readBuffer);
				physx::PxMeshScale scale(physx::PxVec3(1.0f, 1.0f, 1.0f), physx::PxQuat(physx::PxPi * 0.25f, physx::PxVec3(0, 1, 0)));
				physx::PxTriangleMeshGeometry geom(TriMesh);
				physx::PxShape* myConvexMeshShape = GameEnginePhysX::GetPhysics()->createShape(geom, *_Material);

				StaticActor->attachShape(*myConvexMeshShape);
			}
			else
			{
				MsgBoxAssert("Fail Cooking Triangle Mesh");
				return;
			}
		}
	}

	Scene->addActor(*StaticActor);
	PhysXSerialization();
}

void GameEnginePhysXTriMesh::PhysXSerialization()
{
	physx::PxCooking* Cooking = GameEnginePhysX::GetCooking();

	physx::PxSerializationRegistry* registry = physx::PxSerialization::createSerializationRegistry(*GameEnginePhysX::GetPhysics());

	// Create a collection and all objects for serialization
	physx::PxCollection* collection = PxCreateCollection();
	collection->add(*StaticActor);
	physx::PxSerialization::complete(*collection, *registry);

	// Serialize either to binary or RepX
	physx::PxDefaultFileOutputStream outStream("serialized.dat");

	// Binary
	physx::PxSerialization::serializeCollectionToBinary(outStream, *collection, *registry);
	//~Binary

	// RepX
	// physx::PxSerialization::serializeCollectionToXml(outStream, *collection, *registry);

}
