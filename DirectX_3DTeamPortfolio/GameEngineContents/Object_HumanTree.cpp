#include "PreCompile.h"
#include "Object_HumanTree.h"
#include "GameContentsFBXRenderer.h"


Object_HumanTree::Object_HumanTree()
{	
}

Object_HumanTree::~Object_HumanTree()
{
}

void Object_HumanTree::Start()
{

	//11
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer->Transform.AddWorldRotation({ 0, 90 , 0 });
		FBXRenderer->Transform.SetWorldPosition({ -4208, 4121 , -2223 });
	}

	{
		FBXRenderer1 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer1->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer1->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer1->Transform.SetWorldPosition({ -5862, 3373 , -2474 });
	}
	{
		FBXRenderer2 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer2->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer2->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer2->Transform.AddWorldRotation({ 0, -50 , 0 });
		FBXRenderer2->Transform.SetWorldPosition({ -7124, 3400 , -2627 });
	}
	{
		FBXRenderer3 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer3->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer3->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer3->Transform.AddWorldRotation({ 0, -50 , 0 });
		FBXRenderer3->Transform.SetWorldPosition({ -10304, 3630 , -4057 });
	}
	{
		FBXRenderer4 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer4->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer4->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer4->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer4->Transform.SetWorldPosition({ -9779, 3625 , -3386 });
	}
	{
		FBXRenderer5 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer5->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer5->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer5->Transform.AddWorldRotation({ 0, -75 , 0 });
		FBXRenderer5->Transform.SetWorldPosition({ -11954, 2880 , -3783 });
	}
	{
		FBXRenderer6 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer6->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer6->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer6->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer6->Transform.SetWorldPosition({ -15964, 3383 , 2464 });
	}
	{
		FBXRenderer7 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer7->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer7->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer7->Transform.AddWorldRotation({ 0, 30 , 0 });
		FBXRenderer7->Transform.SetWorldPosition({ -16253, 3392 , 786 });
	}
	{
		FBXRenderer8 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer8->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer8->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer8->Transform.AddWorldRotation({ 0, 30 , 0 });
		FBXRenderer8->Transform.SetWorldPosition({ -15684, 2685 , -228 });
	}
	{
		FBXRenderer9 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer9->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer9->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer9->Transform.AddWorldRotation({ 0, -90 , 0 });
		FBXRenderer9->Transform.SetWorldPosition({ -16702, 2760 , -2225 });
	}

	//е╦ют2
	{
		FBXRenderer10 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer10->SetFBXMesh("o302581.FBX", "FBX_Static");
		FBXRenderer10->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer10->Transform.AddWorldRotation({ 0, -110 , 0 });
		FBXRenderer10->Transform.SetWorldPosition({ -3863, 4132 , -829 });
	}
	{
		FBXRenderer11 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer11->SetFBXMesh("o302581.FBX", "FBX_Static");
		FBXRenderer11->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer11->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer11->Transform.SetWorldPosition({ -12805, 2028 , -2796 });
	}
	{
		FBXRenderer12 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer12->SetFBXMesh("o302581.FBX", "FBX_Static");
		FBXRenderer12->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer12->Transform.AddWorldRotation({ 0, 180 , 0 });
		FBXRenderer12->Transform.SetWorldPosition({ -15877, 3390 , 693 });
	}
	{
		FBXRenderer13 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer13->SetFBXMesh("o302581.FBX", "FBX_Static");
		FBXRenderer13->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer13->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer13->Transform.SetWorldPosition({ -16953, 3387 , 1146 });
	}
	{
		FBXRenderer14 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer14->SetFBXMesh("o302581.FBX", "FBX_Static");
		FBXRenderer14->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer14->Transform.AddWorldRotation({ 0, -100 , 0 });
		FBXRenderer14->Transform.SetWorldPosition({ -16724, 2761 , -1474 });
	}
	{
		FBXRenderer15 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer15->SetFBXMesh("o302581.FBX", "FBX_Static");
		FBXRenderer15->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer15->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer15->Transform.SetWorldPosition({ -12679, 2652 , 2944 });
	}
	
	//3
	{
		FBXRenderer16 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer16->SetFBXMesh("o302582.FBX", "FBX_Static");
		FBXRenderer16->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer16->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer16->Transform.SetWorldPosition({ -5616, 3400 , -2408 });
	}
	{
		FBXRenderer17 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer17->SetFBXMesh("o302582.FBX", "FBX_Static");
		FBXRenderer17->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer17->Transform.AddWorldRotation({ 0, -50 , 0 });
		FBXRenderer17->Transform.SetWorldPosition({ -10276, 3635 , -4497 });
	}
	{
		FBXRenderer18 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer18->SetFBXMesh("o302582.FBX", "FBX_Static");
		FBXRenderer18->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer18->Transform.AddWorldRotation({ 0, 60 , 0 });
		FBXRenderer18->Transform.SetWorldPosition({ -16323, 3383 , 1735 });
	}

	//4
	{
		FBXRenderer19 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer19->SetFBXMesh("o302583.FBX", "FBX_Static");
		FBXRenderer19->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer19->Transform.AddWorldRotation({ 0, -90 , 0 });
		FBXRenderer19->Transform.SetWorldPosition({ -7280, 3410 , -3220 });
	}
	{
		FBXRenderer20 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer20->SetFBXMesh("o302583.FBX", "FBX_Static");
		FBXRenderer20->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer20->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer20->Transform.SetWorldPosition({ -10125, 3628 , -3695 });
	}
	{
		FBXRenderer21 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer21->SetFBXMesh("o302583.FBX", "FBX_Static");
		FBXRenderer21->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer21->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer21->Transform.SetWorldPosition({ -12936, 2879 , -3303 });
	}
	{
		FBXRenderer22 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer22->SetFBXMesh("o302583.FBX", "FBX_Static");
		FBXRenderer22->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer22->Transform.AddWorldRotation({ 0, -120 , 0 });
		FBXRenderer22->Transform.SetWorldPosition({ -11593, 2229 , 5327 });
	}
	{
		FBXRenderer23 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer23->SetFBXMesh("o302583.FBX", "FBX_Static");
		FBXRenderer23->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer23->Transform.AddWorldRotation({ 0, 30 , 0 });
		FBXRenderer23->Transform.SetWorldPosition({ -15570, 3392 , 1287 });
	}
	{
		FBXRenderer24 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer24->SetFBXMesh("o302583.FBX", "FBX_Static");
		FBXRenderer24->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer24->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer24->Transform.SetWorldPosition({ -12659, 2020 , -2837 });
	}
	{
		FBXRenderer25 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer25->SetFBXMesh("o302583.FBX", "FBX_Static");
		FBXRenderer25->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer25->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer25->Transform.SetWorldPosition({ -4312, 4131 , -1138 });
	}
	{
		FBXRenderer26 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer26->SetFBXMesh("o302583.FBX", "FBX_Static");
		FBXRenderer26->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer26->Transform.AddWorldRotation({ 0, -60 , 0 });
		FBXRenderer26->Transform.SetWorldPosition({ -6452, 3410 , -2587 });
	}
	{
		FBXRenderer27 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer27->SetFBXMesh("o302583.FBX", "FBX_Static");
		FBXRenderer27->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer27->Transform.AddWorldRotation({ 0, -60 , 0 });
		FBXRenderer27->Transform.SetWorldPosition({ -16699, 2763 , -1721 });
	}

	//5

	{
		FBXRenderer28 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer28->SetFBXMesh("o302584.FBX", "FBX_Static");
		FBXRenderer28->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer28->Transform.AddWorldRotation({ 0, -60 , 0 });
		FBXRenderer28->Transform.SetWorldPosition({ -4181, 4123 , -2059 });
	}
	{
		FBXRenderer29 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer29->SetFBXMesh("o302584.FBX", "FBX_Static");
		FBXRenderer29->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer29->Transform.AddWorldRotation({ 0, -60 , 0 });
		FBXRenderer29->Transform.SetWorldPosition({ 3515, 4130 , -744 });
	}
	{
		FBXRenderer30 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer30->SetFBXMesh("o302584.FBX", "FBX_Static");
		FBXRenderer30->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer30->Transform.AddWorldRotation({ 0, -40 , 0 });
		FBXRenderer30->Transform.SetWorldPosition({ -12085, 2893 , -3772 });
	}
	{
		FBXRenderer31 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer31->SetFBXMesh("o302584.FBX", "FBX_Static");
		FBXRenderer31->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer31->Transform.AddWorldRotation({ 0, -60 , 0 });
		FBXRenderer31->Transform.SetWorldPosition({ -11879, 2143 , 5269 });
	}

	



	
}

void Object_HumanTree::Update(float _Delta)
{

}
