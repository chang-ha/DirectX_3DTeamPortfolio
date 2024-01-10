#pragma once
#include <functional>
#include <map>
#include "GameEnginePacket.h"
#include "GameEngineSerializer.h"

// ���� :
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

	// � ��Ŷ�� ������ ��� ó���� �ſ���?

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
			MsgBoxAssert("�̹� �����ϴ� �ڵ鷯�� �� ��� �Ϸ��� �߽��ϴ�.");
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
					MsgBoxAssert("��Ŷ Ÿ���� ��ġ���� �ʽ��ϴ� ����ó�� Ȯ�����ּ���.");
				}

				_CallBack(Ptr);
			};
	}

	std::shared_ptr<GameEnginePacket> ConvertPacket(int Type, GameEngineSerializer& _Ser)
	{
		if (false == ConvertPacketHandlers.contains(Type))
		{
			MsgBoxAssert("AddHandler�� ������� ���� ��Ŷ�Դϴ�");
			return nullptr;
		}

		return ConvertPacketHandlers[Type](_Ser);
	}

	void ProcessPacket(std::shared_ptr<GameEnginePacket> _Packet)
	{
		if (false == PacketHandlers.contains(_Packet->GetPacketID()))
		{
			MsgBoxAssert("AddHandler�� ������� ���� ��Ŷ�Դϴ�");
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

