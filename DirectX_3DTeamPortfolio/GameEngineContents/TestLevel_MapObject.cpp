#include "PreCompile.h"
#include "TestLevel_MapObject.h"
#include "TestMapObjcet.h"
#include "ContentsLight.h"

TestLevel_MapObject::TestLevel_MapObject()
{

}

TestLevel_MapObject::~TestLevel_MapObject()
{

}

void TestLevel_MapObject::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		std::shared_ptr<TestMapObjcet> Object = CreateActor<TestMapObjcet>(1);
		
	}


}

void TestLevel_MapObject::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestLevel_MapObject::Start()
{
	ContentLevel::Start();



	//Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 0.0f);

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 1, 1 });

	std::shared_ptr<ContentsLight> TestObject0 = CreateActor<ContentsLight>(0);
	/*LightData Data = TestObject0->GetLightData();


	Data.DifLightPower = 0.1f;
	Data.SpcLightPower = 5.0f;
	Data.AmbientLight = float4(0.7f,0.7f,0.7f,1.0f);
	Data.SpcPow = 200.0f;

	TestObject0->SetLightData(Data);*/

	


}

void TestLevel_MapObject::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	//RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);
}

void TestLevel_MapObject::Release()
{

}