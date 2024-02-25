#include "PreCompile.h"
#include "Object_Table.h"
#include "GameContentsFBXRenderer.h"


Object_Table::Object_Table()
{	
}

Object_Table::~Object_Table()
{
}

void Object_Table::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer->Transform.AddWorldRotation({ 0, 100 , 0 });
		FBXRenderer->Transform.SetWorldPosition({ -9420, 2873 , -5022 });
	}

	{
		FBXRenderer1 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer1->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer1->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer1->Transform.AddWorldRotation({ 0, 90 , 0 });
		FBXRenderer1->Transform.SetWorldPosition({ -8970, 2873 , -5022 });
	}
	{
		FBXRenderer2 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer2->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer2->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer2->Transform.AddWorldRotation({ 0, 10 , 0 });
		FBXRenderer2->Transform.SetWorldPosition({ -8320, 2873 , -4772 });
	}
	{
		FBXRenderer3 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer3->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer3->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer3->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer3->Transform.SetWorldPosition({ -8270, 2873 , -4372 });
	}
	{
		FBXRenderer4 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer4->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer4->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer4->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer4->Transform.SetWorldPosition({ -12981, 1630 , 3222 });
	}
	{
		FBXRenderer5 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer5->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer5->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer5->Transform.AddWorldRotation({ 0, 90 , 0 });
		FBXRenderer5->Transform.SetWorldPosition({ -16644, 2324 , 703 });
	}
	{
		FBXRenderer6 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer6->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer6->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer6->Transform.AddWorldRotation({ 0, 110 , 0 });
		FBXRenderer6->Transform.SetWorldPosition({ -17144, 2324 , 853 });
	}
	{
		FBXRenderer7 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer7->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer7->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer7->Transform.AddWorldRotation({ 0, 40 , 0 });
		FBXRenderer7->Transform.SetWorldPosition({ -16380, 2440 , -3867 });
	}
	{
		FBXRenderer8 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer8->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer8->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer8->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer8->Transform.SetWorldPosition({ -15830, 2440 , -3817 });
	}
	{
		FBXRenderer9 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer9->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer9->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer9->Transform.AddWorldRotation({ 0, 60 , 0 });
		FBXRenderer9->Transform.SetWorldPosition({ -11242, 996 , 5644 });
	}
	{
		FBXRenderer10 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer10->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer10->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer10->Transform.AddWorldRotation({ 0, 60 , 0 });
		FBXRenderer10->Transform.SetWorldPosition({ -10892, 996 , 5794 });
	}
	{
		FBXRenderer11 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer11->SetFBXMesh("o101020.FBX", "FBX_Static");
		FBXRenderer11->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer11->Transform.AddWorldRotation({ 0, 50 , 0 });
		FBXRenderer11->Transform.SetWorldPosition({ -11462, 996 , 6044 });
	}

	
}

void Object_Table::Update(float _Delta)
{

}
