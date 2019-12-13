#pragma once
#include"Stage.h"
#include"Door.h"
#include"ScoreBoard.h"

class CBatStage :public CStage
{
private:
	CDoor* Door;
	bool AllowRespawnBat;
	int BatCount;
	DWORD TimeBetWeenBatRespawn;
public:
	CBatStage() { Loadresources(); };
	void Loadresources();
	void Render();
	void DoorRender();
	virtual void Update(DWORD dt, CGrid * CurrentGrid = NULL);
};