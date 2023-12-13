#pragma once

class GameEngineInputLayOutInfo 
{
public:
	static UINT FormatSize(DXGI_FORMAT _Format);

	std::vector<D3D11_INPUT_ELEMENT_DESC> Infos;

	int Offset = 0;

	// 인스턴싱이라는 것을 사용하기 위한 세트 데이터들
	// 인스턴싱은 다수의 동일한 설정을 가진 랜더링 세트를 한번에 그려서 속력을 취하는 것을 말한다.

	void AddInputLayOutDesc(
		LPCSTR _SemanticName, // 내가 포지션이다 내가 컬러다. = "POSITION"
		DXGI_FORMAT _Format, // 내가 n바이트 짜리 정보다 자료형 = DXGI_FORMAT::R32G32 32
		UINT _SemanticIndex = 0, // POSTION0
		UINT _AlignedByteOffset = -1, // 0번째 바이트부터 
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, // 버텍스 데이터가 인스턴싱 데이터다 라는걸 표현
		UINT _InputSlot = 0, // n개의 버텍스 버퍼를 세팅할때 n번째 버텍스 버퍼의 인풋 레이아웃이다 라는걸 표현하는것
		UINT _InstanceDataStepRate = 0 // 나중에 나중에 인스턴싱이라는 구조를 배울때 쓸때가 있을것이다.
	);
};

// 설명 : 버텍스 쉐이더가 필요합니다.
class GameEngineInputLayOut
{
public:
	// constrcuter destructer
	GameEngineInputLayOut();
	~GameEngineInputLayOut();

	// delete Function
	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(GameEngineInputLayOut&& _Other) noexcept = delete;

	void Setting();

	void ResCreate(
		std::shared_ptr<class GameEngineVertexBuffer> _Buffer,
		std::shared_ptr<class GameEngineVertexShader> _Shader
	);

protected:

private:
	ID3D11InputLayout* LayOut = nullptr;



};

