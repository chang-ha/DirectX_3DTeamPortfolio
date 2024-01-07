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
			ImGui::Text("������ �������ϴ�");
			break;
		case NetType::Client:
			ImGui::Text("Ŭ��� �����߽��ϴ�");
			break;
		default:
			break;
		}

		return;
	}

	// ��������
	if (ImGui::Button("Open"))
	{
		NetTypeValue = NetType::Server;
		Server.ServerOpen(30000, 512);

		GameEngineNetWindow::Net = &Server;
	}

	ImGui::InputText("IP", IPBuffer, 100);

	ImGui::SameLine();

	// ���� ����
	if (ImGui::Button("Join"))
	{
		NetTypeValue = NetType::Client;
		Client.Connect(IPBuffer, 30000);

		GameEngineNetWindow::Net = &Client;
	}
}