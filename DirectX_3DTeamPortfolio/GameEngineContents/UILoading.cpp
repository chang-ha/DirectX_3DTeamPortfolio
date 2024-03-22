#include "PreCompile.h"
#include "UILoading.h"


UILoading::UILoading() 
{
	if (nullptr == GameEngineTexture::Find("AKLogo.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UILoadingTexture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFile : Files)
		{
			GameEngineTexture::Load(pFile.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Dark.png");
		GameEngineSprite::CreateSingle("AKLogo.png");
		GameEngineSprite::CreateSingle("UIComments.png");
		GameEngineSprite::CreateSingle("LoadingTemp.png");
		GameEngineSprite::CreateCut("ToiletBowl.dds", 8, 4);
	}
}

UILoading::~UILoading() 
{
}

#define FontSacle 20.0f
#define Yspace 31.0f

void UILoading::Start()
{
	///// 배경
	BackDarkRenderer = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_LoadingBack);
	BackDarkRenderer->SetSprite("Dark.png");
	BackDarkRenderer->SetImageScale(GlobalValue::GetWinScale());
	
	UICommentRenderer = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
	UICommentRenderer->SetSprite("UIComments.png");
	UICommentRenderer->AutoSpriteSizeOn();
	/////

	///// 로고, 팀명, 제작팀원 및 담당분야.
	const float4 CommentHalfScale = UICommentRenderer->GetCurSprite().Texture->GetScale().Half();
	AKLogo = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
	AKLogo->SetSprite("AKLogo.png");
	AKLogo->Transform.SetLocalPosition(float4(-CommentHalfScale.X + 180, CommentHalfScale.Y - 130.0f));
	AKLogo->GetImageTransform().SetLocalScale({ 100.0f, 80.0f });

	TeamName = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
	TeamName->SetText(GlobalValue::OptimusFont, "DARKSOULS™III TEAMPORTFOLIO 3D", 35.0f, float4::WHITE);
	TeamName->Transform.SetLocalPosition(float4(-CommentHalfScale.X + 240.0f, CommentHalfScale.Y - 140.0f));

	ProductionAndField = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
	ProductionAndField->SetText(GlobalValue::OptimusFont, "제작팀원 및 담당분야", 30.0f, float4::WHITE);
	ProductionAndField->Transform.SetLocalPosition(float4(-CommentHalfScale.X + 240.0f, CommentHalfScale.Y - 195.0f));
	/////

	std::shared_ptr<GameEngineUIRenderer> Toilet = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
	Toilet->SetSprite("ToiletBowl.dds");
	Toilet->CreateAnimation("1", "ToiletBowl.dds", 0.1f);
	Toilet->ChangeAnimation("1");
	Toilet->Transform.SetWorldPosition(float4(-778.0f,-337.0f));


	std::shared_ptr<GameEngineUIRenderer> ToiletFont = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
	ToiletFont->SetText(GlobalValue::OptimusFont, "DARK SOULS III", 17.0f, float4(0.9f, 0.9f, 0.9f, 1.0f));
	ToiletFont->Transform.SetLocalPosition(float4(-832.f, -390.f));

	///// 제작자들
	MadesCreateSetName();
	
	///// 조작설명
	ExplainKey();

	Off();
}

void UILoading::Update(float _Delta)
{
}

void UILoading::Release()
{
	BackDarkRenderer = nullptr;
	UICommentRenderer = nullptr;
}

void UILoading::MadesCreateSetName()
{
	const float4 CommentHalfScale = UICommentRenderer->GetCurSprite().Texture->GetScale().Half();
	const float StartXPos = -CommentHalfScale.X + 240.0f;
	const float StartYPos = CommentHalfScale.Y - 235.0f;

	///// 제작자들 
	TeamMember.reserve(8);
	for (int i = 0; i < TeamMember.capacity(); i++)
	{
		Mades = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
		Mades->SetText(GlobalValue::OptimusFont, "이 름 : 담당 / 분야 / 적는 곳", FontSacle, float4::WHITE);
		Mades->Transform.SetLocalPosition(float4(StartXPos, StartYPos - (Yspace*i)));

		//TeamMember.insert(TeamMember.end(), Mades);
		TeamMember.push_back(Mades);
	}

	// 이름 및 담당분야
	TeamMember[0]->SetText(GlobalValue::OptimusFont, "우창하 : 보스 / 엔진 / PHYS X", FontSacle, float4::WHITE);
	TeamMember[1]->SetText(GlobalValue::OptimusFont, "김태훈 : 몬스터 / 툴 에디터", FontSacle, float4::WHITE);
	TeamMember[2]->SetText(GlobalValue::OptimusFont, "김성원 : 몬스터", FontSacle, float4::WHITE);
	TeamMember[3]->SetText(GlobalValue::OptimusFont, "김성균 : 맵 오브젝트", FontSacle, float4::WHITE);
	TeamMember[4]->SetText(GlobalValue::OptimusFont, "김준영 : 맵 / 레벨디자인", FontSacle, float4::WHITE);
	TeamMember[5]->SetText(GlobalValue::OptimusFont, "신원석 : 플레이어", FontSacle, float4::WHITE);
	TeamMember[6]->SetText(GlobalValue::OptimusFont, "유준상 : 쉐이더 / 엔진렌더링", FontSacle, float4::WHITE);
	TeamMember[7]->SetText(GlobalValue::OptimusFont, "홍영현 : UI", FontSacle, float4::WHITE);
	//////////////////

	ExplainStartPos = float4(StartXPos, StartYPos - (Yspace * (TeamMember.capacity() + 1)));
}

void UILoading::ExplainKey()
{

	ExplainText = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
	ExplainText->SetText(GlobalValue::OptimusFont, "조작 설명", 24.0f, float4::WHITE);
	ExplainText->Transform.SetLocalPosition(float4(ExplainStartPos.X, ExplainStartPos.Y));

	ExplainMember.reserve(2);
	for (int i = 0; i < ExplainMember.capacity(); i++)
	{
		Explain = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);
		Explain->SetText(GlobalValue::OptimusFont, "키 : 설명", FontSacle, float4::WHITE);
		Explain->Transform.SetLocalPosition(float4(ExplainStartPos.X, ExplainStartPos.Y - (Yspace * (i + 1))));

		ExplainMember.push_back(Explain);
	}

	ExplainMember[0]->SetText(GlobalValue::OptimusFont, "W/A/S/D : 이동     Q : 시점고정     E : 상호작용     R : 에스트     LSHIFT : 달리기", FontSacle, float4::WHITE);

	ExplainMember[1]->SetText(GlobalValue::OptimusFont, "mLBUTTON : 공격     mRBUTTON : 방어     SPACE BAR : 구르기     L_CTRL : 패링", FontSacle, float4::WHITE);

}