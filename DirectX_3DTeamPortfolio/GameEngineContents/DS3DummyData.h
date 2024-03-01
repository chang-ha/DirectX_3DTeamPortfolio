#pragma once
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineSerializer.h>


class DummyData : public GameEngineSerializObject
{
public:
	void Write(class GameEngineSerializer& _File) override
	{
		_File << Position;
		_File << Forward;
		_File << Upward;
		_File << ReferenceID;
		_File << ParentBoneIndex;
		_File << AttachBoneIndex;
		_File << Flag1;
		_File << Offset;
		_File << Quaternion;
		_File << Local;
		_File << Local_ReversePos;
		_File << Local_NotPos;
	}

	void Read(class GameEngineSerializer& _File) override
	{
		_File >> Position;
		_File >> Forward;
		_File >> Upward;
		_File >> ReferenceID;
		_File >> ParentBoneIndex;
		_File >> AttachBoneIndex;
		_File >> Flag1;
		_File >> Offset;
		_File >> Quaternion;
		_File >> Local;
		_File >> Local_ReversePos;
		_File >> Local_NotPos;

	}

public:
	float4 Position;
	float4 Forward;
	float4 Upward;
	float4 Offset;
	float4 Quaternion;
	float4x4 Local;
	float4x4 Local_ReversePos;
	float4x4 Local_NotPos;
	int ReferenceID = -1;
	int ParentBoneIndex = -1;
	int AttachBoneIndex = -1;
	bool Flag1 = false;

};

// 설명 : 다크소울3에서 특정 뼈를 기준으로 로컬 행렬 변환을 적용받는 기준점입니다.
//			DummyData를 로드하기 전에 필수로 Mesh를 로드해야 사용이 가능합니다.
//		 - 리소스 확장자 명 : .flver.dummyData.json
//		 - 리소스 위치 : ContentsResources/Mesh/(CharacterID)
//		 - 필요한 리소스 파일명 : (CharacterID).MeshFBX
//		 - 생성되는 파일 : (CharacterID).DummyData
class DS3DummyData : public GameEngineResources<DS3DummyData>
{
	enum class eInterpretation
	{
		Coordinate,
		Integer,
		Boolean,
	};

public:
	// constrcuter destructer
	DS3DummyData();
	~DS3DummyData();

	// delete Function
	DS3DummyData(const DS3DummyData& _Other) = delete;
	DS3DummyData(DS3DummyData&& _Other) noexcept = delete;
	DS3DummyData& operator=(const DS3DummyData& _Other) = delete;
	DS3DummyData& operator=(DS3DummyData&& _Other) noexcept = delete;

	static void LoadDummyData(int _ID);

	const DummyData& GetDummyData(int _RefID, int _AttachBoneIndex) const;
	std::map<int, DummyData> GetRefAllData(int _RefID) const;
	std::vector<DummyData> GetDummyDatas() const;

protected:
	static std::string GetExtName();

	static std::string GetFullExtension();

	static std::string GetFormatExt();

	static std::string GetNameToID(int _ID);

	static std::string GetFilePath(std::string_view _Name);

	static void Load(GameEngineFile& _File);

	void Init(std::string_view _Path);
	void DummyInit(std::string_view _Path);
	void Interpret(std::string_view _Data);

	void SetLocalMatrix(DummyData& _DummyPolyData);

	void CreateData(const DummyData& _Data);
	void AllDataWrite(class GameEngineSerializer& _Ser);
	void AllDataRead(class GameEngineSerializer& _Ser);

	template<typename DataType>
	DataType InterpretType(std::string_view _Data, std::string_view _DataName)
	{
		MsgBoxAssert("정의하지 않은 데이터 타입이 존재합니다.");
		return DataType();
	}

	template<>
	int InterpretType(std::string_view _Data, std::string_view _DataName)
	{
		std::string Data = _Data.data();
		size_t StartNum = _Data.find(_DataName);
		if (std::string::npos == StartNum)
		{
			MsgBoxAssert("존재하지 않는 데이터 명입니다.");
			return 0;
		}

		size_t FindXNum;
		size_t EndNum;

		const char* CheckString = " ";
		size_t Len = std::string(CheckString).length();
		FindXNum = Data.find_first_of(CheckString, StartNum) + Len;
		EndNum = Data.find_first_of(',', StartNum);
		std::string Stri = Data.substr(FindXNum, EndNum - FindXNum);
		return std::stoi(Stri);
	}

	template<>
	bool InterpretType(std::string_view _Data, std::string_view _DataName)
	{
		std::string Data = _Data.data();
		size_t StartNum = _Data.find(_DataName);
		if (std::string::npos == StartNum)
		{
			MsgBoxAssert("존재하지 않는 데이터 명입니다.");
			return false;
		}

		size_t FindXNum;
		size_t EndNum;

		const char* CheckString = " ";
		size_t Len = std::string(CheckString).length();
		FindXNum = Data.find_first_of(CheckString, StartNum) + Len;
		EndNum = Data.find_first_of(',', StartNum);
		std::string Strb = Data.substr(FindXNum, EndNum - FindXNum);
		
		return std::string::npos != Strb.compare("true");
	}

	template<>
	float4 InterpretType(std::string_view _Data, std::string_view _DataName)
	{
		std::string Data = _Data.data();
		size_t StartNum = _Data.find(_DataName);
		if (std::string::npos == StartNum)
		{
			MsgBoxAssert("존재하지 않는 데이터 명입니다.");
			return float4::ZERO;
		}

		size_t FindXNum;
		size_t EndNum;

		size_t Len = std::string("X\": ").length();
		FindXNum = Data.find("X\": ", StartNum) + Len;
		EndNum = Data.find_first_of(',', FindXNum);
		std::string XStr = Data.substr(FindXNum, EndNum - FindXNum);
		float XCoor = std::stof(XStr);

		FindXNum = Data.find("Y\": ", StartNum) + Len;
		EndNum = Data.find_first_of(',', FindXNum);
		std::string YStr = Data.substr(FindXNum, EndNum - FindXNum);
		float YCoor = std::stof(YStr);

		FindXNum = Data.find("Z\": ", StartNum) + Len;
		EndNum = Data.find_first_of('\n', FindXNum);
		std::string ZStr = Data.substr(FindXNum, EndNum - FindXNum);
		float ZCoor = std::stof(ZStr);

		return float4(XCoor, YCoor, ZCoor);
	}

private:
	std::multimap<int, DummyData> DummyDataMap;

};

