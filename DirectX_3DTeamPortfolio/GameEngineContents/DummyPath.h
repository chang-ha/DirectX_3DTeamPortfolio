#pragma once

namespace DummyPath
{
	class Node
	{
	public:

	private:

	};

	// Ό³Έν :
	class Path
	{
	public:
		// constrcuter destructer
		Path();
		~Path();

		// delete Function
		Path(const Path& _Other) = delete;
		Path(Path&& _Other) noexcept = delete;
		Path& operator=(const Path& _Other) = delete;
		Path& operator=(Path&& _Other) noexcept = delete;

	protected:

	private:


	};
}



