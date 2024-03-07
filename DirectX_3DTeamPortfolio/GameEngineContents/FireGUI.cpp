#include "PreCompile.h"
#include "FireGUI.h"
#include "ContentsFireRenderer.h"

FireGUI::FireGUI() 
{
}

FireGUI::~FireGUI()
{
}

void FireGUI::Start()
{
}

void FireGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ShowList(_Level);
	FireEditor( _DeltaTime);
}

void FireGUI::LevelEnd()
{
}

void FireGUI::ShowList(GameEngineLevel* _Level)
{
	if (true == CObjectNames.empty())
	{
		const std::list<std::shared_ptr<GameEngineObject>>& ObjectGroup = _Level->GetObjectGroupInt(static_cast<int>(Enum_UpdateOrder::Component));
		if (ObjectGroup.empty())
		{
			return;
		}

		CObjectNames.reserve(ObjectGroup.size());
		ActorNames.reserve(ObjectGroup.size());
		int Cnt = 0;

		for (const std::shared_ptr<GameEngineObject>& Object : ObjectGroup)
		{
			ActorNames.push_back(Object->GetName());
			CObjectNames.push_back(ActorNames[Cnt].c_str());
			Cnt++;
		}
	}

	static int SelectActorIndex = 0;

	if (ImGui::ListBox("ActorList", &SelectActorIndex, &CObjectNames[0], static_cast<int>(CObjectNames.size())))
	{
		std::string ActorName = CObjectNames[SelectActorIndex];

		RendererPtr.clear();
		RendererNames.clear();
		CRendererNames.clear();
		if (true == ActorName.empty())
		{
			return;
		}

		const std::vector<std::shared_ptr<GameEngineObject>>& ObjectGroup = _Level->GetObjectGroupConvert<GameEngineObject>(Enum_UpdateOrder::Component);

		for (const std::shared_ptr<GameEngineObject>& Object : ObjectGroup)
		{
			if (CObjectNames[SelectActorIndex] == Object->GetName())
			{
				SelectActor = Object.get();

				const std::vector<std::shared_ptr<GameEngineRenderer>>& RendererGroup = SelectActor->GetObjectGroupConvert<GameEngineRenderer>(Enum_RenderOrder::Effect);
				int Cnt = 0;
				for (const std::shared_ptr<GameEngineRenderer>& Renderer : RendererGroup)
				{
					if ("" != Renderer->GetName())
					{
						RendererPtr.push_back(Renderer);
						RendererNames.push_back(Renderer->GetName());
						CRendererNames.push_back(RendererNames[Cnt].c_str());

						Cnt++;
					}
				}

			}
		}
	}


	if (SelectActor != nullptr)
	{
		if (ImGui::ListBox("RendererList", &SelectActorIndex, &CRendererNames[0], static_cast<int>(CRendererNames.size())))
		{
			SelectRenderer= RendererPtr[SelectActorIndex].get();
		}
	}


}

void FireGUI::FireEditor(float _DeltaTime)
{

	if (nullptr != SelectRenderer)
	{
		float4 Pos = SelectRenderer->Transform.GetLocalPosition();

		//float4 Scale = static_cast<GameEngineSpriteRenderer*>(SelectRenderer)->GetAutoScaleRatio();

		//float ScaleTotal = Scale.X;

		//ImGui::SliderFloat3("Pos", &Pos.X, -100.0f, 100.0f);
		ImGui::InputFloat3("Pos", &Pos.X);
		//ImGui::SliderFloat("Scale", &ScaleTotal, 0.0f, 1.0f);

		SelectRenderer->Transform.SetLocalPosition(Pos);

		//Scale = float4(ScaleTotal, ScaleTotal, ScaleTotal);

		//static_cast<GameEngineSpriteRenderer*>(SelectRenderer)->SetAutoScaleRatio(Scale);
		ImGui::Text("");
	}

	if (ContentsFireRenderer::MainFire != nullptr)
	{
		FireInfo Info = ContentsFireRenderer::MainFire->FireInfoValue;

		bool callback = false;


		ImGui::SliderFloat("TimeScale", &ContentsFireRenderer::MainFire->TimeScale, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scrollSpeeds1", &Info.scrollSpeeds1, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scrollSpeeds2", &Info.scrollSpeeds2, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scrollSpeeds3", &Info.scrollSpeeds3, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scales1", &Info.scales1, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scales2", &Info.scales2, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("scales3", &Info.scales3, 0.0f, 5.0f);


		callback = ImGui::SliderFloat3("distortion1", &Info.distortion1.X, -0.0f, 1.0f);
		callback = ImGui::SliderFloat3("distortion2", &Info.distortion2.X, -0.0f, 1.0f);
		callback = ImGui::SliderFloat3("distortion3", &Info.distortion3.X, -0.0f, 1.0f);

		callback = ImGui::SliderFloat("distortionScale", &Info.distortionScale, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("distortionBias", &Info.distortionBias, 0.0f, 5.0f);
		callback = ImGui::SliderFloat("perturbscale", &Info.perturbscale, 0.0f, 5.0f);


		
			ContentsFireRenderer::MainFire->FireInfoValue = Info;
		
	}
}
