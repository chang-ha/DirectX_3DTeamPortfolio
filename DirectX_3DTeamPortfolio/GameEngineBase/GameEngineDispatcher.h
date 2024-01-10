#pragma once
#include <functional>
#include <map>
#include "GameEnginePacket.h"
#include "GameEngineSerializer.h"

// 설명 :
class GameEngineDispatcher
{
public:
	// constrcuter destructer
	GameEngineDispatcher();
	~GameEngineDispatcher();

	// delete Function
	GameEngineDispatcher(const GameEngineDispatcher& _Other) = delete;
	GameEngineDispatcher(GameEngineDispatcher&& _Other) noexcept = delete;
	GameEngineDispatcher& operator=(const GameEngineDispatcher& _Other) = delete;
	GameEngineDispatcher& operator=(GameEngineDispatcher&& _Other) noexcept = delete;

	// 어떤 패킷이 왔을때 어떻게 처리할 거에요?

	template<typename PacketType>
	void AddHandler(std::function<void(std::shared_ptr<PacketType>)> _CallBack)
	{
		int Type = static_cast<int>(PacketType::Type);
		AddHandler(Type, _CallBack);
	}

	template<typename PacketType>
	void AddHandler(int Type, std::function<void(std::shared_ptr<PacketType>)> _CallBack)
	{
		if (true == PacketHandlers.contains(Type))
		{
			MsgBoxAssert("이미 존재하는 핸들러를 또 등록 하려고 했습니다.");
		}

		ConvertPacketHandlers[Type] = [=](GameEngineSerializer& _Ser/*, void* _Data, size_t Size*/)
			{
				// ObjectUpdate
				std::shared_ptr<PacketType> NewPacket = std::make_shared<PacketType>();
				NewPacket->DeSerializePacket(_Ser);
				return NewPacket;
			};

		PacketHandlers[Type] = [=](std::shared_ptr<GameEnginePacket> _Packet)
			{
				// std::shared_ptr<ObjectUpdate> Ptr = std::dynamic_pointer_cast<ObjectUpdate>(_Packet);
				std::shared_ptr<PacketType> Ptr = std::dynamic_pointer_cast<PacketType>(_Packet);

				if (nullptr == Ptr)
				{
					MsgBoxAssert("패킷 타입이 일치하지 않습니다 디스페처를 확인해주세요.");
				}

				_CallBack(Ptr);
			};
	}

	std::shared_ptr<GameEnginePacket> ConvertPacket(int Type, GameEngineSerializer& _Ser)
	{
		if (false == ConvertPacketHandlers.contains(Type))
		{
			MsgBoxAssert("AddHandler를 등록하지 않은 패킷입니다");
			return nullptr;
		}

		return ConvertPacketHandlers[Type](_Ser);
	}

	void ProcessPacket(std::shared_ptr<GameEnginePacket> _Packet)
	{
		if (false == PacketHandlers.contains(_Packet->GetPacketID()))
		{
			MsgBoxAssert("AddHandler를 등록하지 않은 패킷입니다");
			return;
		}

		PacketHandlers[_Packet->GetPacketID()](_Packet);
	}



protected:


private:
	std::map<int, std::function<std::shared_ptr<GameEnginePacket>(GameEngineSerializer& _Ser)>> ConvertPacketHandlers;

	std::map<int, std::function<void(std::shared_ptr<GameEnginePacket>)>> PacketHandlers;
	// std::map<int, std::function<void(std::shared_ptr<ConnetPacket>)>> PacketHandlers;
};

