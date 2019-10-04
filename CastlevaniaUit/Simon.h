#pragma once
#include"GameObject.h"
#include"SimonSprites.h"

class CSimon :public CGameObject
{
private:
	static CSimon* instance;
	unordered_map<SimonState, LPANIMATION> animations;
	LPANIMATION currentanimation;
public:
	CSimon();
	~CSimon();
	LPANIMATION getCurrentAnimation() { return currentanimation; }
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	static CSimon* GetInstance();
	void Render();
};