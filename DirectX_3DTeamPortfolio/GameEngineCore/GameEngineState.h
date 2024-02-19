#pragma once


class CreateStateParameter
{
public:
	// 진짜 맴버변수를 가질수는 없다.
	std::function<void(class GameEngineState* _Parent)> Init;
	std::function<void(class GameEngineState* _Parent)> Start;
	std::function<void(float DeltaTime, class GameEngineState* _Parent)> Stay;
	std::function<void(class GameEngineState* _Parent)> End;
};

class State
{
public:
	std::string Name;

	CreateStateParameter Event;
};


// 설명 :
class GameEngineState
{
public:
	template<typename EnumType>
	void ChangeState(EnumType _Stateindex)
	{
		return ChangeState(static_cast<int>(_Stateindex));
	}

	void ChangeState(int _Stateindex)
	{
		if (nullptr != CurState && nullptr != CurState->Event.End)
		{
			CurState->Event.End(this);
		}

		CurState = &States[_Stateindex];

		if (nullptr != CurState && nullptr != CurState->Event.Start)
		{
			CurState->Event.Start(this);
		}

		StateTime = 0.0f;
	}

	template<typename EnumType>
	void CreateState(EnumType _Stateindex, const CreateStateParameter& _Para, std::string_view _Name = "")
	{
		return CreateState(static_cast<int>(_Stateindex), _Para, _Name);
	}

	void CreateState(int _Stateindex, const CreateStateParameter& _Para, std::string_view _Name = "")
	{
		States[_Stateindex].Name = _Name;
		States[_Stateindex].Event = _Para;
	}



	template<typename EnumType>
	void Find(EnumType _Stateindex)
	{
		return Find(static_cast<int>(_Stateindex));
	}

	State* Find(int _Index)
	{
		if (false == States.contains(_Index))
		{
			return nullptr;
		}
		return &States[_Index];
	}

	void Update(float _DeltaTime)
	{
		StateTime += _DeltaTime;

		if (nullptr == CurState || nullptr == CurState->Event.Stay)
		{
			return;
		}

		CurState->Event.Stay(_DeltaTime, this);
	}

	float GetStateTime() 
	{
		return StateTime;
	}

	const std::map<int, State>* GetAllStates()
	{
		return &States;
	}

	int GetCurState() const
	{
		if (nullptr == CurState)
		{
			return -1;
		}

		for (const std::pair<const int, State>& Pair : States)
		{
			if (CurState == &Pair.second)
			{
				return Pair.first;
			}
		}

		MsgBoxAssert("현재 상태가 이상합니다.")
		return -1;
	}

protected:

private:
	float StateTime = 0.0f;
	State* CurState = nullptr;
	std::map<int, State> States;
};

