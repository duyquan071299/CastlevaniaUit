#pragma once
#include"Animations.h"
class CAnimationDatabase
{
	static CAnimationDatabase * instance;

	unordered_map<AniType, unordered_map<State,LPANIMATION>> animations;
	
	

public:

	void Add(AniType type, unordered_map<State, LPANIMATION>);
	LPANIMATION Get(AniType type, State ObjectState);
	void LoadAnimation();
	static CAnimationDatabase * GetInstance();
};