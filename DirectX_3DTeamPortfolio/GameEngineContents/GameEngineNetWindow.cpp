#include "PreCompile.h"
#include "GameEngineNetWindow.h"
#include "ConnectIDPacket.h"
#include "ObjectPacket.h"
#include "Player.h"
#include <memory>

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

	// ��������
	if (ImGui::Button("Open"))
	{
		NetTypeValue = NetType::Server;
		Server.ServerOpen(30000, 512);

		// �÷��̾����� ���̵� �ο��ؾ� �Ѵ�.
		{
			int ID = GameEngineNetObject::CreateServerObjectID();
			MainPlayer->SetObjectID(ID);
			MainPlayer->SetContorllType(ControllType::Play);
		}

		Server.SetAcceptCallBack(
			[=](SOCKET _ClientSocket, GameEngineNetServer* _Server)
			{
				// ������� ó������ �� N���̾߸� �˷���� �Ѵ�.
				std::shared_ptr<ConnectIDPacket> Packet = std::make_shared<ConnectIDPacket>();

				int ID = GameEngineNetObject::CreateServerObjectID();
				Packet->SetObjectID(ID);

				_Server->GameEngineNet::SendPacket(_ClientSocket, Packet);
			}
		);

		GameEngineNetWindow::Net = &Server;
	}

	ImGui::InputText("IP", IPBuffer, 100);

	ImGui::SameLine();

	// ���� ����
	if (ImGui::Button("Join"))
	{
		NetTypeValue = NetType::Client;
		Client.Connect(IPBuffer, 30000);

		MainPlayer->SetContorllType(ControllType::Play);

		GameEngineNetWindow::Net = &Client;
	}
}