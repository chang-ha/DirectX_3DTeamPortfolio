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

	// 서버열기
	if (ImGui::Button("Open"))
	{
		NetTypeValue = NetType::Server;
		Server.ServerOpen(30000, 512);

		// 플레이어한테 아이디를 부여해야 한다.
		{
			int ID = GameEngineNetObject::CreateServerObjectID();
			MainPlayer->SetObjectID(ID);
			MainPlayer->SetContorllType(ControllType::Play);
		}

		Server.SetAcceptCallBack(
			[=](SOCKET _ClientSocket, GameEngineNetServer* _Server)
			{
				// 상대한테 처음으로 너 N번이야를 알려줘야 한다.
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

	// 서버 들어가기
	if (ImGui::Button("Join"))
	{
		NetTypeValue = NetType::Client;
		Client.Connect(IPBuffer, 30000);

		MainPlayer->SetContorllType(ControllType::Play);

		GameEngineNetWindow::Net = &Client;
	}
}