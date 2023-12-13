#pragma once
#include <vector>
#include "GameEngineDebug.h"
#include "GameEngineMath.h"

// ���������� ��ǻ���� ��� �����ʹ� ����Ʈ ������ �Ҽ� �ִ�.
// �� ����Ʈ ����� ���� ���ϴ� ��ŭ ���� ���ϴ� ������ 
// �о���̰ų� ��Ʈ���Ҽ� �ְ� ������ִ� Ŭ���� �̴�.


class GameEngineSerializObject
{
public:
	virtual void Write(class GameEngineSerializer& _File) = 0;
	virtual void Read(class GameEngineSerializer& _File) = 0;
};


// ���� :
class GameEngineSerializer
{
public:
	// constrcuter destructer
	GameEngineSerializer();
	~GameEngineSerializer();

	void Write(const void* Data, unsigned int _Size);
	void operator<<(std::string_view _Value);
	void operator<<(const std::string& _Value);
	void operator<<(const int& _Value);
	void operator<<(const unsigned int& _Value);
	void operator<<(const uint64_t& _Value);
	void operator<<(const float& _Value);
	void operator<<(const bool& _Value);
	void operator<<(const float4& _Value);
	void operator<<(const float4x4& _Value);



	template<typename Value>
	void operator<<(std::vector<Value>& _Data)
	{
		unsigned int Size = static_cast<unsigned int>(_Data.size());
		operator<<(Size);

		if (Size <= 0)
		{
			return;
		}

		for (size_t i = 0; i < _Data.size(); i++)
		{
			if (false == std::is_base_of<GameEngineSerializObject, Value>::value)
			{
				Write(&_Data[i], sizeof(Value));
			}
			else
			{
				GameEngineSerializObject* Ser = reinterpret_cast<GameEngineSerializObject*>(&_Data[i]);
				Ser->Write(*this);
			}
		}
	}


	template<typename Key, typename  Value>
	void operator<<(std::map<Key, Value>& _Data)
	{
		unsigned int Size = static_cast<unsigned int>(_Data.size());
		Write(Size);

		if (Size <= 0)
		{
			return;
		}

		for (std::pair<Key, Value> Pair : _Data)
		{
			if (false == std::is_base_of<GameEngineSerializObject, Key>::value)
			{
				Write(Pair.first);
			}
			else
			{
				GameEngineSerializObject* Ser = reinterpret_cast<GameEngineSerializObject*>(&Pair.first);
				Ser->Write(*this);
			}

			if (false == std::is_base_of<GameEngineSerializObject, Value>::value)
			{
				Write(Pair.second);
			}
			else
			{
				GameEngineSerializObject* Ser = reinterpret_cast<GameEngineSerializObject*>(&Pair.second);
				Ser->Write(*this);
			}
		}
	}


	void Read(void* Data, unsigned int _Size);
	void operator>>(std::string& _Value);
	void operator>>(int& _Value);
	void operator>>(unsigned int& _Value);
	void operator>>(uint64_t& _Value);
	void operator>>(float& _Value);
	void operator>>(bool& _Value);
	void operator>>(float4& _Value);
	void operator>>(float4x4& _Value);


	template<typename Value>
	void operator>>(std::vector<Value>& _Data)
	{
		unsigned int Size = 0;
		operator>>(Size);

		if (Size <= 0)
		{
			return;
		}

		_Data.resize(Size);

		for (unsigned int i = 0; i < Size; i++)
		{
			if (false == std::is_base_of<GameEngineSerializObject, Value>::value)
			{
				Read(&_Data[i], sizeof(Value));
			}
			else
			{
				GameEngineSerializObject* Ser = reinterpret_cast<GameEngineSerializObject*>(&_Data[i]);
				Ser->Read(*this);
			}

		}
	}

	template<typename Key, typename  Value>
	void operator>>(std::map<Key, Value>& _Data)
	{
		unsigned int Size = 0;
		Read(Size);

		if (Size <= 0)
		{
			return;
		}

		for (unsigned int i = 0; i < Size; ++i)
		{
			std::pair<Key, Value> Pair;

			if (false == std::is_base_of<GameEngineSerializObject, Key>::value)
			{
				Read(Pair.first);
			}
			else
			{
				GameEngineSerializObject* Ser = reinterpret_cast<GameEngineSerializObject*>(&Pair.first);
				Ser->Read(*this);
			}


			if (false == std::is_base_of<GameEngineSerializObject, Value>::value)
			{
				Read(Pair.second);
			}
			else
			{
				GameEngineSerializObject* Ser = reinterpret_cast<GameEngineSerializObject*>(&Pair.second);
				Ser->Read(*this);
			}

			_Data.insert(Pair);
		}
	}


	std::string_view GetStringView();

	//// delete Function
	//GameEngineSerializer(const GameEngineSerializer& _Other) = delete;
	//GameEngineSerializer(GameEngineSerializer&& _Other) noexcept = delete;
	//GameEngineSerializer& operator=(const GameEngineSerializer& _Other) = delete;
	//GameEngineSerializer& operator=(GameEngineSerializer&& _Other) noexcept = delete;

	void BufferResize(size_t _BufferSize)
	{
		Data.resize(_BufferSize);
	}

	size_t GetBufferSize()
	{
		return Data.size();
	}

	size_t GetWriteOffset()
	{
		return WriteOffset;
	}


	template<typename PtrType>
	PtrType* GetDataPtr()
	{
		return reinterpret_cast<PtrType*>(&Data[0]);
	}

protected:

private:
	// �ϰ� ���� ���� �ٸ��� �����̰�.
	unsigned int WriteOffset = 0;
	unsigned int ReadOffset = 0;

	// �̷� Ŭ������ �ִٸ�
	// ���� ���ų� ���ϼ��� �ִ�.
	std::vector<char> Data;
};


// �̷� Ŭ������ �׳� �����ص� �ǿ�.
//struct PlayData
//{
//	int A;
//	int B;
//	int C;
//};

// 
//struct PlayData
//{
//	int A;
//	int B;
//	int C;
// std::string Name;
//};

class GameEngineSerializerObject
{
public:
	// ��ü => File(byte ���)
	virtual void Serializer(GameEngineSerializer& _Data) = 0;

	// File(byte ���) => ��ü
	virtual void DeSerializer(GameEngineSerializer& _Data) = 0;
};