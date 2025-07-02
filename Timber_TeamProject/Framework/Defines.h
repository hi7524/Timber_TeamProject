#pragma once

// Defines.h

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Title,		//(캐릭터 선택,스테이지 선택 분기로),
	Choice,
	Game,		//(1인플레이 씬)
	Dev1,
	Dev2,		//(2인플레이 씬),
	Ending,		//(엔딩 씬)
	Count		//(count)
};

enum class Sides
{
	Left,
	Right,
	None,
};