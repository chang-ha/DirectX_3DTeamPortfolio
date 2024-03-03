#include "PreCompile.h"
#include "Object_CandleHuman.h"
#include "GameContentsFBXRenderer.h"


Object_CandleHuman::Object_CandleHuman()
{	
}

Object_CandleHuman::~Object_CandleHuman()
{
}

void Object_CandleHuman::Start()
{
	//1
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer->Transform.SetWorldPosition({ -6611, 3400 , -3566 });
	}

	/*{
		FBXRenderer1 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer1->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer1->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer1->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer1->Transform.SetWorldPosition({ -7111, 3400 , -3766 });
	}*/
	{
		FBXRenderer2 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer2->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer2->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer2->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer2->Transform.SetWorldPosition({ -7511, 3400 , -3966 });
	}
	{
		FBXRenderer3 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer3->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer3->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer3->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer3->Transform.SetWorldPosition({ -7111, 3470 , -4116 });
	}
	{
		FBXRenderer4 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer4->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer4->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer4->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer4->Transform.SetWorldPosition({ -6961, 3482 , -4016 });
	}
	{
		FBXRenderer5 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer5->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer5->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer5->Transform.AddWorldRotation({ 0, -60 , 0 });
		FBXRenderer5->Transform.SetWorldPosition({ -6355, 3480 , -4178 });
	}
	{
		FBXRenderer6 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer6->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer6->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer6->Transform.AddWorldRotation({ 0, -40 , 0 });
		FBXRenderer6->Transform.SetWorldPosition({ -5805, 3485 , -3878 });
	}
	{
		FBXRenderer7 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer7->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer7->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer7->Transform.AddWorldRotation({ 0, 30 , 0 });
		FBXRenderer7->Transform.SetWorldPosition({ -11664, 2887 , -4428 });
	}
	{
		FBXRenderer8 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer8->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer8->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer8->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer8->Transform.SetWorldPosition({ -11764, 2887 , -4428 });
	}
	{
		FBXRenderer9 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer9->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer9->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer9->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer9->Transform.SetWorldPosition({ -12648, 2890 , -4339 });
	}
	//2
	{
		FBXRenderer10 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer10->SetFBXMesh("o302566.FBX", "FBX_Static");
		FBXRenderer10->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer10->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer10->Transform.SetWorldPosition({ -7092, 3400 , -3759 });
	}

	{
		FBXRenderer11 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer11->SetFBXMesh("o302566.FBX", "FBX_Static");
		FBXRenderer11->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer11->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer11->Transform.SetWorldPosition({ -5651, 3490 , -3813 });
	}
	{
		FBXRenderer12 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer12->SetFBXMesh("o302566.FBX", "FBX_Static");
		FBXRenderer12->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer12->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer12->Transform.SetWorldPosition({ -5399, 3480 , -3308 });
	}
	{
		FBXRenderer13 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer13->SetFBXMesh("o302566.FBX", "FBX_Static");
		FBXRenderer13->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer13->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer13->Transform.SetWorldPosition({ -12379, 2970 , -4687 });
	}
	{
		FBXRenderer14 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer14->SetFBXMesh("o302566.FBX", "FBX_Static");
		FBXRenderer14->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer14->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer14->Transform.SetWorldPosition({ -12166, 2888 , -4414 });
	}

}

void Object_CandleHuman::Update(float _Delta)
{

}
