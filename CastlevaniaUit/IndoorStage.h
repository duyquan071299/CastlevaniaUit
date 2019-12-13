#pragma once
#include"Stage.h"
#include"Door.h"
#include"ScoreBoard.h"

class CIndoorStage :public CStage
{
	
private:
	CDoor* Door;
	DWORD TimeBetWeenGhostRespawn;
	int GhostCount;
	bool AllowRespawnGhost;
	int PantherCount;
	int PantherAtX1;
	int PantherAtX2;
	int PantherAtX3;
public:
	CIndoorStage() { Loadresources(); };
	void Loadresources();
	void DoorRender();
	void Render();
	virtual void Update(DWORD dt, CGrid * CurrentGrid = NULL);
};