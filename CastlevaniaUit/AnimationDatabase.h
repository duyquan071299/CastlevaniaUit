#pragma once
#include"Animations.h"
class CAnimationDatabase
{
	static CAnimationDatabase * instance;

	unordered_map<GraphicType, LPANIMATION> animations;

public:
	void Add(GraphicType type, LPANIMATION ani);
	LPANIMATION Get(GraphicType type);
	void LoadAnimation();
	static CAnimationDatabase * GetInstance();
};