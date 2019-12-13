#pragma once
#include"Stage.h"
#include"ScoreBoard.h"

class CBossStage :public CStage
{

private:
	DWORD TimeBetWeenGhostRespawn;
	int GhostCount;
	bool AllowRespawnGhost;
public:
	CBossStage() { Loadresources(); };
	void Loadresources();
	void DoorRender();
	void Render();
	virtual void Update(DWORD dt, CGrid * CurrentGrid = NULL);
};