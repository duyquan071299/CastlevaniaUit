#pragma once
#include"GlobalObject.h"
#include"SpriteDatabase.h"
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	bool isLastFrame;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(GraphicType type, int index, DWORD time = 0);
	void Render(float x, float y, int alpha = 255);
	bool IsLastFrame() { return isLastFrame; }
};

typedef CAnimation *LPANIMATION;