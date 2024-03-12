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
	FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	FBXRenderer->SetFBXMesh("o001020.FBX", "FBX_Static");
	FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
}

void Object_Table::Update(float _Delta)
{

}
