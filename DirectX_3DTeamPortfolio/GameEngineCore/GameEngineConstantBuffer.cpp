#include "PreCompile.h"
#include "GameEngineConstantBuffer.h"

std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> GameEngineConstantBuffer::ConstantBuffers;

GameEngineConstantBuffer::GameEngineConstantBuffer() 
{
}

GameEngineConstantBuffer::~GameEngineConstantBuffer() 
{
}

void GameEngineConstantBuffer::ResCreate(int _ByteSize)
{
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferInfo.ByteWidth = _ByteSize;

	// 안바꿈
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	//                                                                 초기화
	if (S_OK != GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void GameEngineConstantBuffer::VSSetting(UINT _Slot)
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert(std::string(GetName()) + "만들어지지 않은 상수버퍼를 세팅하려고 했습니다.");
	}

	GameEngineCore::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
}

void GameEngineConstantBuffer::PSSetting(UINT _Slot)
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert(std::string(GetName()) + "만들어지지 않은 상수버퍼를 세팅하려고 했습니다.");
	}

	GameEngineCore::GetContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
}

void GameEngineConstantBuffer::CSSetting(UINT _Slot)
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert(std::string(GetName()) + "만들어지지 않은 상수버퍼를 세팅하려고 했습니다.");
	}

	GameEngineCore::GetContext()->CSSetConstantBuffers(_Slot, 1, &Buffer);
}

void GameEngineConstantBuffer::GSSetting(UINT _Slot)
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert(std::string(GetName()) + "만들어지지 않은 상수버퍼를 세팅하려고 했습니다.");
	}

	GameEngineCore::GetContext()->GSSetConstantBuffers(_Slot, 1, &Buffer);
}

void GameEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
	if (nullptr == _Data)
	{
		std::string Name = GetName().data();
		MsgBoxAssert(Name + "nullptr인 데이터를 세팅하려고 했습니다.");
		return;
	}

	// 크기가 다른
	if (_Size != BufferInfo.ByteWidth)
	{
		std::string Name = GetName().data();
		MsgBoxAssert(Name + "크기가 다른 데이터로 상수버퍼를 세팅하려고 했습니다.");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE Data = {};

	// 그래픽카드는 초고속으로 랜더링 연산을 
	// 병렬적으로 실행한다.
	// 그러므로 데이터를 CPU에서 데이터를 변경한다는 것은
	// 그래픽카드에게 예약하는 형태가 됩니다.
	// 그리고 그런 예약 대부분은 그래픽카드를 느리게 만듭니다.
	// 잠깐 그리는거 멈춰봐 그리는데 필요한 데이터를 새로 가져왔어
	// 최대한 1번에 세팅하는 구조가 최고다.
	// map을 호출하는 횟수가 문제다.
	// 벡터가 모든 자료구조중에서 가장 빠른 이유도 여기에 있습니다.
	// 하지만 그런구조를 짜면 편의성에 문제가 생기기 때문에 그냥 많이 할겁니다.
	
	// 이 버퍼를 잠깐 쓰지마 잠궈 데이터 변경할거야.
	GameEngineCore::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	// 그래픽카드에 직접 슬수있는 주소값을 담아줍니다.
	// Data

	if (Data.pData == nullptr)
	{
		std::string Name = Name;
		MsgBoxAssert(Name + "버퍼 수정 권한을 얻어내지 못했습니다.");
		return;
	}

	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);
	


	// 다썼어.
	GameEngineCore::GetContext()->Unmap(Buffer, 0);
}