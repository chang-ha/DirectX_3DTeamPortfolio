#pragma once
#include "GameEngineResources.h"
#include "GameEngineDirectBuffer.h"

enum class StructuredBufferType
{
	NONE,
	SRV_ONLY, // => 쉐이더 리소스로만 사용하겠다.
	UAV_INC, // => 컴퓨트 쉐이더에 넣어서 사용하고 결과값을 적용 받겠다.
};


// 스트럭처드 버퍼는 동적으로 데이터의 크기도 변경할수 있어요.
// 메모리를 아껴야 한다.
// 이녀석도 상수버퍼랑 비슷하게 기본 설계가 달라져야 합니다.

// 설명 :
class GameEngineStructuredBuffer : public GameEngineResources<GameEngineStructuredBuffer>, public GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineStructuredBuffer();
	~GameEngineStructuredBuffer();

	// delete Function
	GameEngineStructuredBuffer(const GameEngineStructuredBuffer& _Other) = delete;
	GameEngineStructuredBuffer(GameEngineStructuredBuffer&& _Other) noexcept = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer& _Other) = delete;
	GameEngineStructuredBuffer& operator=(GameEngineStructuredBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineStructuredBuffer> Find(int _Byte)
	{
		if (false == StructuredBufferRes.contains(_Byte))
		{
			return nullptr;
		}

		return StructuredBufferRes[_Byte];
	}

	static std::shared_ptr<GameEngineStructuredBuffer> CreateAndFind(int _Byte, void* _StartData = nullptr)
	{
		std::shared_ptr<GameEngineStructuredBuffer> FindBuffer = Find(_Byte);

		if (nullptr != FindBuffer)
		{
			return FindBuffer;
		}

		std::shared_ptr<GameEngineStructuredBuffer> NewBuffer = CreateRes();
		NewBuffer->DataSize = _Byte;
		return NewBuffer;
	}


	static std::shared_ptr<GameEngineStructuredBuffer> CreateAndFind(int _Byte, std::string_view _Name, void* _StartData = nullptr)
	{
		std::shared_ptr<GameEngineStructuredBuffer> FindBuffer = Find(_Byte);

		if (nullptr != FindBuffer)
		{
			return FindBuffer;
		}

		std::shared_ptr<GameEngineStructuredBuffer> NewBuffer = CreateRes(_Name);
		NewBuffer->DataSize = _Byte;
		return NewBuffer;
	}

	int GetDataSize() 
	{
		return DataSize;
	}

	inline StructuredBufferType GetStructuredBufferType()
	{
		return Type;
	}

	inline void SetStructuredBufferType(StructuredBufferType _Type)
	{
		Type = _Type;
	}

	void CreateResize(int _Byte, int _Count, StructuredBufferType _Type, const void* _StartData = nullptr);

	void Release();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
	void CSSetting(UINT _Slot);
	void GSSetting(UINT _Slot);

	void VSReset(UINT _Slot);
	void PSReset(UINT _Slot);
	void CSReset(UINT _Slot);
	void GSReset(UINT _Slot);

	void ChangeData(const void* _Data, size_t _Size);

	void SetData(void* _pSrc, size_t _Count);

protected:


private:
	ID3D11ShaderResourceView* SRV = nullptr; // 쉐이더에 세팅해줄수 있는 권한.
	ID3D11UnorderedAccessView* UAV = nullptr; // 컴퓨트쉐이더에서 결과를 받아오는 용도의 권한.
	D3D11_MAPPED_SUBRESOURCE SettingResources = {};

	ID3D11Buffer* WriteBuffer = nullptr;
	ID3D11Buffer* ReadBuffer = nullptr;

	int DataSize = 0;
	int DataCount = 0;
	StructuredBufferType Type = StructuredBufferType::NONE;

	// 
	//                         전체크기가 x
	//                        40바이트크기의 10개 버퍼
	//                        40바이트만 의미한다.
	static std::map<int, std::shared_ptr < GameEngineStructuredBuffer>> StructuredBufferRes;
};

