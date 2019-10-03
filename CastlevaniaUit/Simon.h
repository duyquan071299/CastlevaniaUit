#pragma once
#include"GameObject.h"
#include"SimonSprites.h"

class CSimon :public CGameObject
{
private:
	static CSimon* instance;
	unordered_map<SimonState, LPANIMATION> animations;
public:
	CSimon();
	~CSimon();
	static CSimon* GetInstance();
	void Render();
};