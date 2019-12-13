#include "StageManager.h"

CStageManager * CStageManager::instance = NULL;

CStageManager::CStageManager()
{

}

CStageManager::~CStageManager()
{
}

CStageManager * CStageManager::GetInstance()
{
	if (!instance)
	{
		instance = new CStageManager();
	}
	return instance;
}


void CStageManager::Update(DWORD dt)
{
	CurrentStage->Update(dt);
}


void CStageManager::LoadStage(CStage * newStage)
{
	delete this->CurrentStage;
	this->CurrentStage = newStage;
}

CStage * CStageManager::GetCurrentStage()
{
	return this->CurrentStage;
}
