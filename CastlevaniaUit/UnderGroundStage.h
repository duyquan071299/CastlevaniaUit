#pragma once
#include"Stage.h"
#include"ScoreBoard.h"



class CUnderGroundStage :public CStage
{
private:
	int KappaCount;
	DWORD TimeBetWeenKappaRespawn;
	bool FirstRespawn;
	DWORD TimeLimit;
	bool AllowRespawnKappa;
public:
	CUnderGroundStage() { Loadresources(); };
	void Loadresources();
	void Render();
	virtual void Update(DWORD dt, CGrid * CurrentGrid = NULL);
};