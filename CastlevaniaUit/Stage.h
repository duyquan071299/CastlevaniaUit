#pragma once
#include"GlobalObject.h"
#include"ScoreBoard.h"
#include"Simon.h"
#include"Grid.h"

class CStage
{
protected:
	int MapBoundLeft;
	int MapBoundRight;
	string StageLevel;
	int CurrentStageType;

public:
	int GetMapBoundLeft() { return MapBoundLeft; }
	int GetMapBoundRight() { return MapBoundRight; }
	void SetMapBound(int MBL, int MBR) { MapBoundLeft = MBL; MapBoundRight = MBR; }
	virtual void Loadresources() {};
	virtual void Render() {};
	virtual void DoorRender() {};
	virtual void Update(DWORD dt,CGrid * CurrentGrid=NULL) {};
	string GetStageLevel() { return this->StageLevel; }
	int GetStageType() { return this->CurrentStageType; }

};