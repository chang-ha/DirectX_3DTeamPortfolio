#include "PreCompile.h"
#include "TestLevel_PhysX.h"


TestLevel_PhysX::TestLevel_PhysX()
{

}

TestLevel_PhysX::~TestLevel_PhysX()
{

}

void TestLevel_PhysX::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
}

void TestLevel_PhysX::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}

void TestLevel_PhysX::Start()
{
	ContentLevel::Start();
	//// Test Code
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	//														정적마찰, 동적마찰, 복원
	//physx::PxMaterial* gMaterial = Physics->createMaterial(0.5f, 0.5f, 0.6f);

	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 2.0f);

	// create simulation
	physx::PxMaterial* mMaterial = Physics->createMaterial(0.5f, 0.5f, 0.6f);
	// Ground
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);

	// Box
	float halfExtent = 10.5f;
	physx::PxShape* Boxshape = Physics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *mMaterial);
	physx::PxShape* Sphereshape = Physics->createShape(physx::PxSphereGeometry(10), *mMaterial);
	physx::PxShape* CapsuleShape = Physics->createShape(physx::PxCapsuleGeometry(5, 20), *mMaterial); // 캡슐이 똑바로 서있는 모양은 1/4Pi 만큼 회전 필요
	physx::PxTransform t(physx::PxVec3(0));
	physx::PxQuat Quat = physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1));
	physx::PxTransform localTm(physx::PxVec3(0.0f, 3.0f, -100.0f), Quat);
	physx::PxRigidDynamic* DynamicActor = Physics->createRigidDynamic(localTm);
	DynamicActor->attachShape(*Boxshape);
	physx::PxRigidBodyExt::updateMassAndInertia(*DynamicActor, 10.0f);
	physx::PxU32 Num = Scene->getNbActors(physx::PxActorTypeFlag::eRIGID_DYNAMIC);
	
	Scene->addActor(*DynamicActor);
	// DynamicActor->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, false);

	//physx::PxRigidStatic* StaticActor = Physics->createRigidStatic(localTm);
	//StaticActor->attachShape(*CapsuleShape);
	//Scene->addActor(*StaticActor);

	// physx::PxU32 size = 30;
	//for (physx::PxU32 i = 0; i < size; i++) {
	//	for (physx::PxU32 j = 0; j < size - i; j++) {
	//		physx::PxTransform localTm(physx::PxVec3(physx::PxReal(j * 2) - physx::PxReal(size - i), physx::PxReal(i * 2 + 1), 0) * halfExtent);
	//		physx::PxRigidDynamic* body = Physics->createRigidDynamic(t.transform(localTm));
	//		body->attachShape(*shape);
	//		physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
	//		Scene->addActor(*body);
	//	}
	//}

	Boxshape->release();
	Sphereshape->release();
	CapsuleShape->release();

	// CookingTestCode();
}

void TestLevel_PhysX::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TestLevel_PhysX::Release()
{

}

using namespace physx;

void TestLevel_PhysX::CookingTestCode()
{
	std::string FileName = "c1240.FBX";

	GameEngineFile File;
	File.MoveParentToExistsChild("ContentsResources");
	File.MoveChild("ContentsResources");
	File.MoveChild("Mesh");
	File.MoveChild("Monster");
	File = File.PlusFilePath(FileName);

	File.ChangeExtension(".MeshFBX");

	if (false == File.IsExits())
	{
		std::shared_ptr<GameEngineActor> TriActor = CreateActor<GameEngineActor>();
		std::shared_ptr<GameEngineFBXRenderer> FBXRENDERER = TriActor->CreateComponent<GameEngineFBXRenderer>();
		FBXRENDERER->SetFBXMesh(FileName, "FBXStaticColor");
		TriActor->Death();
	}

	File.Open(FileOpenType::Read, FileDataType::Binary);
	GameEngineSerializer Ser;
	File.DataAllRead(Ser);

	std::string FBXMeshName;
	std::vector<FbxExMeshInfo> MeshInfos;
	std::vector<FbxRenderUnitInfo> RenderUnitInfos;
	std::vector<Bone> AllBones;
	Ser >> FBXMeshName;
	Ser >> MeshInfos;
	Ser >> RenderUnitInfos;
	Ser >> AllBones;


	FbxRenderUnitInfo& UnitInfo = RenderUnitInfos[0];
	std::vector<PxVec3> Vertexs;
	Vertexs.resize(UnitInfo.Vertexs.size());

	for (int i = 0; i < UnitInfo.Vertexs.size(); i++)
	{
		const float4 Position = UnitInfo.Vertexs[i].POSITION; 
		Vertexs[i].x = Position.X;
		Vertexs[i].y = Position.Y;
		Vertexs[i].z = Position.Z;
	}

	if (true)
	{
		PxTriangleMeshDesc meshDesc;
		meshDesc.points.count = static_cast<PxU32>(Vertexs.size());
		meshDesc.points.stride = sizeof(PxVec3);
		meshDesc.points.data = &Vertexs[0];

		meshDesc.triangles.count = static_cast<PxU32>(UnitInfo.Indexs[0].size() / 3);
		meshDesc.triangles.stride = 3 * sizeof(PxU32);
		meshDesc.triangles.data = &UnitInfo.Indexs[0];

		if (meshDesc.isValid())
		{
			PxDefaultMemoryOutputStream writeBuffer;

			if (GameEnginePhysX::GetCooking()->cookTriangleMesh(meshDesc, writeBuffer))
			{
				PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
				PxTriangleMesh* TriMesh = GameEnginePhysX::GetPhysics()->createTriangleMesh(readBuffer);
				PxMeshScale scale(PxVec3(100.0f, 100.0f, 100.0f), PxQuat(PxPi * 0.25f, PxVec3(0, 1, 0)));
				PxTriangleMeshGeometry geom(TriMesh);
				PxShape* myConvexMeshShape = GameEnginePhysX::GetPhysics()->createShape(geom, *GameEnginePhysX::GetDefaultMaterial());

				physx::PxRigidStatic* staticActor = GameEnginePhysX::GetPhysics()->createRigidStatic(PxTransform(PxVec3(0.0f)));
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
}