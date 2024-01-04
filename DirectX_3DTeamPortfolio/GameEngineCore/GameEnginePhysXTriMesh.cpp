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

}

void GameEnginePhysXTriMesh::PhysXComponentInit(std::string_view _MeshName, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Find(_MeshName);

	std::vector<FbxRenderUnitInfo> RenderUnitInfos = Mesh->GetRenderUnitInfos();

	for (int i = 0; i < RenderUnitInfos.size(); i++)
	{
		FbxRenderUnitInfo& UnitInfo = RenderUnitInfos[i];
		std::vector<physx::PxVec3> Vertexs;
		std::vector<physx::PxVec3> Indexs;
		Vertexs.resize(UnitInfo.Vertexs.size());
		// Indexs.resize(UnitInfo.Indexs.size());

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
				physx::PxMeshScale scale(physx::PxVec3(100.0f, 100.0f, 100.0f), physx::PxQuat(physx::PxPi * 0.25f, physx::PxVec3(0, 1, 0)));
				physx::PxTriangleMeshGeometry geom(TriMesh);
				physx::PxShape* myConvexMeshShape = GameEnginePhysX::GetPhysics()->createShape(geom, *GameEnginePhysX::GetDefaultMaterial());

				physx::PxRigidStatic* staticActor = GameEnginePhysX::GetPhysics()->createRigidStatic(physx::PxTransform(physx::PxVec3(0.0f)));
				staticActor->attachShape(*myConvexMeshShape);
				Scene->addActor(*staticActor);
			}
			else
			{
				MsgBoxAssert("Fail Cooking Triangle Mesh");
				return;
			}
		}
	}

	//for (int i = 0; i < RenderUnitInfos.size(); i++)
	//{
	//	FbxRenderUnitInfo& UnitInfo = RenderUnitInfos[0];
	//	std::vector<PxVec3> Vertexs;
	//	Vertexs.resize(UnitInfo.Vertexs.size());

	//	for (int i = 0; i < UnitInfo.Vertexs.size(); i++)
	//	{
	//		const float4 Position = UnitInfo.Vertexs[i].POSITION;
	//		Vertexs[i].x = Position.X;
	//		Vertexs[i].y = Position.Y;
	//		Vertexs[i].z = Position.Z;
	//	}

	//	if (true)
	//	{
	//		PxTriangleMeshDesc meshDesc;
	//		meshDesc.points.count = static_cast<PxU32>(Vertexs.size());
	//		meshDesc.points.stride = sizeof(PxVec3);
	//		meshDesc.points.data = &Vertexs[1];

	//		meshDesc.triangles.count = static_cast<PxU32>(UnitInfo.Indexs[0].size() / 3);
	//		meshDesc.triangles.stride = 3 * sizeof(PxU32);
	//		meshDesc.triangles.data = &UnitInfo.Indexs[0];

	//		if (meshDesc.isValid())
	//		{
	//			PxDefaultMemoryOutputStream writeBuffer;

	//			if (GameEnginePhysX::GetCooking()->cookTriangleMesh(meshDesc, writeBuffer))
	//			{
	//				PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	//				PxTriangleMesh* TriMesh = GameEnginePhysX::GetPhysics()->createTriangleMesh(readBuffer);
	//				PxMeshScale scale(PxVec3(100.0f, 100.0f, 100.0f), PxQuat(PxPi * 0.25f, PxVec3(0, 1, 0)));
	//				PxTriangleMeshGeometry geom(TriMesh);
	//				PxShape* myConvexMeshShape = GameEnginePhysX::GetPhysics()->createShape(geom, *GameEnginePhysX::GetDefaultMaterial());

	//				physx::PxRigidStatic* staticActor = GameEnginePhysX::GetPhysics()->createRigidStatic(PxTransform(PxVec3(0.0f)));
	//				staticActor->attachShape(*myConvexMeshShape);
	//				Scene->addActor(*staticActor);
	//			}
	//			else
	//			{
	//				MsgBoxAssert("Fail Cooking Triangle Mesh");
	//				return;
	//			}
	//		}
	//	}
	//}

}