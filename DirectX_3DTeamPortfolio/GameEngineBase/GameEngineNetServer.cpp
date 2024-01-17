#include "PreCompile.h"
#include "GameEngineNetServer.h"
#include "GameEngineDebug.h"

void GameEngineNetServer::AcceptThread(SOCKET _AcceptSocket, GameEngineNetServer* _Net)
{
    int AddressLen = sizeof(SOCKADDR_IN);
    while (_Net->IsRun)
    {
        SOCKADDR_IN ClientAdd;

        memset(&ClientAdd, 0, sizeof(ClientAdd));

        SOCKET ClientSocket = accept(_AcceptSocket, (sockaddr*)&ClientAdd, &AddressLen);

        if (SOCKET_ERROR == ClientSocket || INVALID_SOCKET == ClientSocket)
        {
            return;
        }

        std::shared_ptr<GameEngineThread> NewThread = std::make_shared<GameEngineThread>();
        _Net->ServerRecvThreads.push_back(NewThread);

        // ClientSocket�� ���� ��ġ�� �ʾ� Ű�� �Ǿ �ɰ��̴�.
        std::string ThreadName = std::to_string(ClientSocket);
        ThreadName += "Server Recv Thread";

        if (nullptr == _Net->AcceptCallBack)
        {
            MsgBoxAssert("����Ʈ �Լ��� �������� ���� ���·� ������ �������׽��ϴ�.");
        }

        _Net->AcceptCallBack(ClientSocket, _Net);

        NewThread->Start(ThreadName, std::bind(&GameEngineNet::RecvThreadFunction, ClientSocket, _Net));

    }
}

GameEngineNetServer::GameEngineNetServer() 
{
}

GameEngineNetServer::~GameEngineNetServer() 
{
    for (std::pair<int, SOCKET> SocketPair : Users)
    {
        closesocket(SocketPair.second);
    }

    if (0 != AcceptSocket)
    {
        closesocket(AcceptSocket);
    }
}



void GameEngineNetServer::ServerOpen(short _Port, int _BackLog)
{
    WSAData WsaData;

    int errorCode = WSAStartup(MAKEWORD(2, 2), &WsaData);
    if (SOCKET_ERROR == errorCode)
    {
        MsgBoxAssert("socket Error");
        return;
    }

    SOCKADDR_IN Add;
    Add.sin_family = AF_INET; // ip4�ּ� ü�踦 ���ڴ�.
    Add.sin_port = htons(_Port); // ��Ʈ��ũ ��ſ� ��ȿ�� ����� ������� ������ش�.
    if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Add.sin_addr))
    {
        return;
    }

    AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == AcceptSocket)
    {
        return;
    }

    if (SOCKET_ERROR == bind(AcceptSocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
    {
        return;
    }

    BackLog = _BackLog;

    if (SOCKET_ERROR == listen(AcceptSocket, _BackLog))
    {
        return;
    }

    Thread.Start("AcceptThread", std::bind(GameEngineNetServer::AcceptThread, AcceptSocket, this));
}

void GameEngineNetServer::Disconnect(SOCKET _Socket)
{
    // ���� ���� ������������ �޼��� �ȶ��� �����.

    std::mutex UserLock;

    std::map<int, SOCKET>::iterator StartIter = Users.begin();
    std::map<int, SOCKET>::iterator EndIter = Users.end();

    for (; StartIter != EndIter; )
    {
        if (StartIter->second != _Socket)
        {
            ++StartIter;
            continue;
        }

        StartIter = Users.erase(StartIter);

        //std::string Text = std::to_string(StartIter->first);
        //Text += " �� ������ ������ �����߽��ϴ�.";
        //MessageBoxA(nullptr, Text.c_str(), "���� ����", MB_OK);

    }
}

void GameEngineNetServer::RecvProcess(char* _Data)
{

}

void GameEngineNetServer::SendPacket(std::shared_ptr<GameEnginePacket> _Packet)
{
    // �̰� ������ ���� ���ڱ� �����ڰ� ������
    std::lock_guard<std::mutex> Lock(UserLock);

    GameEngineSerializer Ser;
    _Packet->SerializePacket(Ser);

    for (std::pair<const int, SOCKET>& pair : Users)
    {
        if (pair.first == _Packet->GetObjectID())
        {
            continue;
        }

        GameEngineNet::Send(pair.second, Ser);
    }
}