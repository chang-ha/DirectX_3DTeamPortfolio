#include "PreCompile.h"
#include "GameEngineNetWindow.h"

GameEngineNet* GameEngineNetWindow::Net = nullptr;


GameEngineNetWindow::GameEngineNetWindow()
{
}

GameEngineNetWindow::~GameEngineNetWindow()
{
}

void GameEngineNetWindow::Start()
{
}

void GameEngineNetWindow::OnGUI(class GameEngineLevel* _Level, float _DeltaTime)
{
	if (NetTypeValue != NetType::None)
	{
		switch (NetTypeValue)
		{
		case NetType::Server:
			ImGui::Text("Server Open");
			break;
		case NetType::Client:
			ImGui::Text("Client Join");
			break;
		default:
			break;
		}

		return;
	}

	// 서버열기
	if (ImGui::Button("Open"))
	{
		NetTypeValue = NetType::Server;
		Server.ServerOpen(30000, 512);

		Server.SetAcceptCallBack(
			[=](SOCKET _ClientSocket, GameEngineNetServer* _Server, int ID)
			{
				// 상대한테 처음으로 너 N번이야를 알려줘야 한다.

				int a = 0;
			}
		);

		GameEngineNetWindow::Net = &Server;
	}

	ImGui::InputText("IP", IPBuffer, 100);

	ImGui::SameLine();

	// 서버 들어가기
	if (ImGui::Button("Join"))
	{
		NetTypeValue = NetType::Client;
		Client.Connect(IPBuffer, 30000);

		GameEngineNetWindow::Net = &Client;
	}
}