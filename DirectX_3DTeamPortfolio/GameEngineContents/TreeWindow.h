#pragma once

class TreeObject : public std::enable_shared_from_this<TreeObject>
{
	friend class TreeWindow;
	friend class RootTree;

public:
	TreeObject() {}
	virtual ~TreeObject() {}

	virtual void Start() {}
	virtual void OnGUI(GameEngineLevel* _Level, float _DeltaTime) {}
	virtual void LevelEnd() {}

	std::string_view GetName()const { return Name; }

	template <typename ObjectType>
	std::shared_ptr<ObjectType> CreateTree(std::string_view _Name)
	{
		std::shared_ptr<ObjectType> NewTree = std::make_shared<ObjectType>();
		NewTree->ParentTree = this;
		NewTree->Name = _Name;
		NewTree->Init(NewTree);
		ChildTrees.push_back(NewTree);
		return NewTree;
	}

	TreeObject* ParentTree = nullptr; // 부모트리 
	
protected:
	void AllOnGUI(GameEngineLevel* _Level, float _DeltaTime);
	void AllLevelEnd();
	void Init(std::shared_ptr<TreeObject> _Object);

protected:
	std::vector<std::shared_ptr<TreeObject>> ChildTrees; // 자식 트리

private:
	std::string Name;



};

class RootTree : public TreeObject
{
	friend class TreeWindow;

private:
	void Start() override;

};

// 설명 :
class TreeWindow : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	void CreateRootTree()
	{
		std::shared_ptr<RootTree> NewTree = std::make_shared<RootTree>();
		NewTree->Start();
		Root = NewTree;
	}

private:
	std::shared_ptr<RootTree> Root;
	class GameEngineLevel* Level = nullptr;

};