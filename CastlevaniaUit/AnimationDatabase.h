#pragma once
#include"Animations.h"
class CAnimationDatabase
{
	static CAnimationDatabase * instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(GraphicType type, LPANIMATION ani);
	LPANIMATION Get(GraphicType type);

	static CAnimationDatabase * GetInstance();
};
