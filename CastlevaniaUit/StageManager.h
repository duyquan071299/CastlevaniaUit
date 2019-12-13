#pragma once
#include "Stage.h"

class CStageManager
{
private:
	static CStageManager * instance;
	CStage * CurrentStage;

public:

	static CStageManager * GetInstance();
	CStageManager();
	CStage * GetCurrentStage();

	~CStageManager();


	void LoadStage(CStage * newStage);

	void Update(DWORD dt);
};

