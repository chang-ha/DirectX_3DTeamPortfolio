#pragma once

// ���� :
class DummyNode
{
public:
	// constrcuter destructer
	DummyNode();
	~DummyNode();

	// delete Function
	DummyNode(const DummyNode& _Other) = delete;
	DummyNode(DummyNode&& _Other) noexcept = delete;
	DummyNode& operator=(const DummyNode& _Other) = delete;
	DummyNode& operator=(DummyNode&& _Other) noexcept = delete;

protected:

private:


};

