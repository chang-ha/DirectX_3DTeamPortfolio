#pragma once

enum class ECAMERAORDER
{
	MainPrev,
	Main,
	MainNext,
	UI,
};

enum class EPROJECTIONTYPE
{
	Perspective,
	Orthographic,
};


enum class ShaderType
{
	None = 0, // 맨앞에 None를 넣어주는 사람은 에러를 체크하려는 사람들이 많이 쓴다.
	Vertex, // 필수
	Hull,
	Tessellator,
	Domain,
	Geometry,
	Pixel, // 필수<
	Compute,
	Max, // max는 for문돌리거나 할때 필요하니까.
};
