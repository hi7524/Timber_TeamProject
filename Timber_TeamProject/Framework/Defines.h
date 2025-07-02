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
	Title,
	Single,
	Multi,
	SelectMod,
	Game,
	Difficulty,
	Dev1,
	Dev2,
	CharChoiceMulti,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};