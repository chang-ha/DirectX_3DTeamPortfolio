#include "PreCompile.h"
#include "FogGUI.h"
#include <GameEngineCore\FogEffect.h>

FogGUI::FogGUI() 
{
}

FogGUI::~FogGUI()
{
}

void FogGUI::Start()
{
}

void FogGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	LUTEditor(_Level);
}


void FogGUI::LevelEnd()
{

}

void FogGUI::LUTEditor(GameEngineLevel* _Level)
{
	//std::list<std::shared_ptr<Effect>> Effects = _Level->GetMainCamera()->GetCameraDeferredTarget()->GetEffects();


	////std::vector<std::shared_ptr<ObjectType>> Result;
	////std::list<std::shared_ptr<class GameEngineObject>>& Group = Childs[_GroupIndex];

	//for (std::shared_ptr<class Effect> Ptr : Effects)
	//{
	//	// 컴파일타임어써션을 통해서 애초에 이게 가능한 일인지 알수 있는데
	//	// 빠르게 만들어야 하니까.
	//	std::shared_ptr<FogEffect> Ptr = Obejct->GetDynamic_Cast_This<ObjectType>();

	//	std::shared_ptr<GameEngineObject> ObjectPtr = shared_from_this();
	//	std::shared_ptr<ConvertType> CameraPtr = std::dynamic_pointer_cast<ConvertType>(ObjectPtr);

	//	if (nullptr == CameraPtr)
	//	{
	//		// MsgBoxAssert("다이나믹 캐스트에 실패했습니다. 가상함수 테이블 부모가 누구인지 확인해보세요. 혹은 부모 생성자에서는 사용이 불가능한 함수입니다.");
	//		return nullptr;
	//	}

	//	return CameraPtr;

	//	if (nullptr == Ptr)
	//	{
	//		continue;
	//	}

	//	Result.push_back(Ptr);
	//}

	//return Result;

	//if (FogEffectPtr == nullptr)
	//{
	//	return;
	//}

	//FogInfo Info = *FogEffect::MainFogInfo;
	FogInfo InfoSlieder = *FogEffect::MainFogInfo;

	ImGui::SliderFloat3("FogColor", &InfoSlieder.FogColor.X, -0.0f, 1.0f);
	//ImGui::InputFloat3("FogColor", &Info.FogColor.X);

	ImGui::SliderFloat("FogMaxHeight", &InfoSlieder.FogMaxHeight, -3000.0f, 3000.0f);
	//ImGui::InputFloat("FogMinHeight", &Info.FogMinHeight);

	ImGui::SliderFloat("FogMinHeight", &InfoSlieder.FogMinHeight, -3000.0f, 3000.0f);
	//ImGui::InputFloat("FogMaxHeight", &Info.FogMaxHeight);

	ImGui::SliderFloat("NoiseScale", &InfoSlieder.NoiseScale, 0.0f, 100.0f);
	ImGui::SliderFloat("NoiseOffset", &InfoSlieder.NoiseOffset, 0.0f, 100.0f);
	ImGui::SliderFloat("NoiseIntensity", &InfoSlieder.NoiseIntensity, -0.0f, 100.0f);

	//*FogEffect::MainFogInfo = Info;
	*FogEffect::MainFogInfo = InfoSlieder;


}
