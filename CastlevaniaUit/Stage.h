#pragma once
#include"GlobalObject.h"
#include"Simon.h"
#include"Grid.h"

class CStage
{
protected:
	int MapBoundLeft;
	int MapBoundRight;
public:
	int GetMapBoundLeft() { return MapBoundLeft; }
	int GetMapBoundRight() { return MapBoundRight; }
	void SetMapBound(int MBL, int MBR) { MapBoundLeft = MBL; MapBoundRight = MBR; }
	virtual void Loadresources() {};
	virtual void Render() {};
	virtual void DoorRender() {};
	virtual void Update(DWORD dt,CGrid * CurrentGrid=NULL) {};

};