#include "PreCompile.h"
#include "GameEngineSprite.h"

float4 SpriteData::GetScale()
{
	return Texture->GetScale() * float4( SpritePivot.Scale2DX, SpritePivot.Scale2DY, 1.0f, 0.0f);
}

GameEngineSprite::GameEngineSprite() 
{
}

GameEngineSprite::~GameEngineSprite() 
{
}

// 이미지가 1장 있는데 그 이미지를 잘라서 랜더링하는 
void GameEngineSprite::ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
{
	// 기본생성자가 있는 자료형은 내부에서 만든다.
	// std::vector

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스처로 스프라이트를 만들려고 했습니다.");
		return;
	}

	SpriteDatas.resize(_X * _Y);

	float4 Start;
	Start.Pos2DX = 0.0f;
	Start.Pos2DY = 0.0f;
	Start.Scale2DX = 1.0f / _X;
	Start.Scale2DY = 1.0f / _Y;

	for (size_t y = 0; y < _Y; ++y)
	{
		for (size_t x = 0; x < _X; x++)
		{
			unsigned int index = static_cast<unsigned int>((y * _X) + x);
			SpriteDatas[index].Texture = Texture;
			SpriteDatas[index].SpritePivot = Start;
			Start.Pos2DX += Start.Scale2DX;
		}

		Start.Pos2DX = 0.0f;
		Start.Pos2DY += Start.Scale2DY;
	}
	

	// GameEngineTexture::Find(_Name);


}

SpriteData GameEngineSprite::GetSpriteData(unsigned int _Index)
{
	if (_Index >= SpriteDatas.size())
	{
		MsgBoxAssert("인덱스를 오버해서 스프라이트 데이터를 가져오려고 했습니다.");
		return SpriteData();
	}

	return SpriteDatas[_Index];
}

void GameEngineSprite::ResCreateFolder(std::string_view _Path)
{
	GameEngineDirectory Dir = _Path;

	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	SpriteDatas.resize(Files.size());

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineFile& File = Files[i];
		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(File.GetStringPath());

		SpriteDatas[i].Texture = Texture;
		SpriteDatas[i].SpritePivot = float4(0, 0, 1.0f, 1.0f);
	}
}