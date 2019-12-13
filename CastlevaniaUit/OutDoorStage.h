#pragma once
#include"Stage.h"


class COutDoorStage:public CStage
{

private:
	LPSPRITE HiddenDoor;
public:
	void Loadresources();
	void Render();
	virtual void Update(DWORD dt, CGrid * CurrentGrid=NULL);
	void DrawHiddenDoor();
	void DoorRender() {};
	COutDoorStage() { Loadresources(); }
};