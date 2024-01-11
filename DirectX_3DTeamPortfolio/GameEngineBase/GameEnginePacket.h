#pragma once
#include <memory>
#include "GameEngineSerializer.h"

// �̹�ĵ� ������ �ִ� ��
//class MovePacket
//{
//	float4 Pos;
//	float4 Dir;
//	float4 Move;
//	float Speed;
//};

// ���� :
class GameEnginePacket : public std::enable_shared_from_this<GameEnginePacket>
{
public:
	// constructer destructer
	GameEnginePacket();
	virtual ~GameEnginePacket();

	// delete Function
	GameEnginePacket(const GameEnginePacket& _Other) = delete;
	GameEnginePacket(GameEnginePacket&& _Other) noexcept = delete;
	GameEnginePacket& operator = (const GameEnginePacket& _Other) = delete;
	GameEnginePacket& operator = (GameEnginePacket&& _Other) noexcept = delete;

	template<typename EnumType>
	void SetPacketID(EnumType _PacketID)
	{
		PacketID = static_cast<int>(_PacketID);
	}

	void SetPacketID(int _PacketID)
	{
		PacketID = _PacketID;
	}

	void SetObjectID(int _ObjectID)
	{
		ObjectID = _ObjectID;
	}

	int GetSize(){
		return Size;
	}

	template<typename EnumType>
	EnumType GetPacktID(){
		return static_cast<EnumType>(PacketID);
	}

	int GetPacketID(){
		return PacketID;
	}
	int GetObjectID() {
		return ObjectID;
	}

	void SerializePacket(GameEngineSerializer& _Ser)
	{
		Serialize(_Ser);
		SerializeEnd(_Ser);
	}


	virtual void Serialize(GameEngineSerializer& _Ser)
	{
		_Ser << Size;
		_Ser << PacketID;
		_Ser << ObjectID;
	}

	virtual void SerializeEnd(GameEngineSerializer& _Ser)
	{
		Size = _Ser.GetWriteOffsetInt();

		if (0 >= Size)
		{
			MsgBoxAssert("0 ����Ʈ ��Ŷ�� �����Ǿ����ϴ�.");
		}

		int* SizePtr = _Ser.GetDataPtr<int*>();
		*SizePtr = Size;
	}

	void DeSerializePacket(GameEngineSerializer& _Ser)
	{
		DeSerialize(_Ser);
	}

	virtual void DeSerialize(GameEngineSerializer& _Ser)
	{
		_Ser >> Size;
		_Ser >> PacketID;
		_Ser >> ObjectID;
	}


protected:

private:
	int Size = -1; // <= ��Ŷ�� ũ��
	int PacketID = -1; // <= �����ε� int�� ó���Ѵ�.
	int ObjectID = -1; // <= � ������Ʈ�� ���´�.
};

