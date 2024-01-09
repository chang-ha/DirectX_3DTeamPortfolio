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

        // ClientSocket은 절대 겹치지 않아 키가 되어도 될것이다.
        std::string ThreadName = std::to_string(ClientSocket);
        ThreadName += "Server Recv Thread";

        if (nullptr == _Net->AcceptCallBack)
        {
            MsgBoxAssert("엑셉트 함수를 세팅하지 않은 상태로 서버를 가동시켰습니다.");
        }

        int ID = -1;

        {
            ID = _Net->SOCKETID++;

            std::lock_guard<std::mutex> Lock(_Net->UserLock);
            _Net->Users.insert(std::pair(ID, ClientSocket));
        }

        _Net->AcceptCallBack(ClientSocket, _Net, ID);

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
    Add.sin_family = AF_INET; // ip4주소 체계를 쓰겠다.
    Add.sin_port = htons(_Port); // 네트워크 통신에 유효한 에디안 방식으로 만들어준다.
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

void GameEngineNetServer::RecvProcess(char* _Data)
{

}