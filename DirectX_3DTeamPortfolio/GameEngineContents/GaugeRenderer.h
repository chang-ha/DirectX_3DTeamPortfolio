#pragma once

// Ό³Έν :
class GaugeRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GaugeRenderer();
	~GaugeRenderer();

	// delete Function
	GaugeRenderer(const GaugeRenderer& _Other) = delete;
	GaugeRenderer(GaugeRenderer&& _Other) noexcept = delete;
	GaugeRenderer& operator=(const GaugeRenderer& _Other) = delete;
	GaugeRenderer& operator=(GaugeRenderer&& _Other) noexcept = delete;

	static void MaterialLoad();

	void SetSprite(std::string_view _Name, unsigned int index = 0);

	inline void SetAutoScaleRatio(float _Ratio)
	{
		AutoScaleRatio.X = _Ratio;
		AutoScaleRatio.Y = _Ratio;
	}

	inline void SetAutoScaleRatio(float4 _Ratio)
	{
		AutoScaleRatio = _Ratio;
	}

	void SetImageScale(const float4& _Scale);
	void AddImageScale(const float4& _Scale);

	void AutoSpriteSizeOn()
	{
		IsImageSize = true;
	}

	void AutoSpriteSizeOff()
	{
		IsImageSize = false;
	}

	std::shared_ptr<GameEngineSprite> GetSprite()
	{
		return Sprite;
	}

	const SpriteData& GetCurSprite()
	{
		return CurSprite;
	}

	inline GameEngineTransform& GetImageTransform()
	{
		return ImageTransform;
	}

	inline GaugeInfo& GetGaugeInfo()
	{
		return GaugeInfoValue;
	}

	void SetGauge(float _Ratio);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void SetMaterialEvent(std::string_view _Name, int _Index) override;

	void BillboardUpdate(float4 _CameraRotation) override;

private:
	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;
	GaugeInfo GaugeInfoValue;

	float4 AutoScaleRatio = { 1.0f,1.0f,1.0f };

	GameEngineTransform ImageTransform;

	bool IsImageSize = false;
	bool IsUserSampler = true;
};
