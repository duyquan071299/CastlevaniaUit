#pragma once
#include"Stage.h"
#include"ScoreBoard.h"

class CBossStage :public CStage
{

private:
	DWORD TimeBetWeenGhostRespawn;
	int GhostCount;
	bool AllowRespawnGhost;
	DWORD TimeOrbAppear;
	bool IsBossDie;
public:
	CBossStage() { Loadresources(); };
	void BossDieTime()
	{
		IsBossDie = true;
		TimeOrbAppear = GetTickCount();
	}
	void Loadresources();
	void DoorRender();
	void Render();
	virtual void Update(DWORD dt, CGrid * CurrentGrid = NULL);
};