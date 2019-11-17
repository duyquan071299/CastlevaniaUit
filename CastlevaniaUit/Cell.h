#pragma once
#include "GameObject.h"

class CCell
{
private:
	int ID;
	vector<LPGAMEOBJECT> listObject;
public:
	CCell() {};
	~CCell() {};
	void AddObject(LPGAMEOBJECT Object);
	int GetID() {
		return ID;
	}

	vector<LPGAMEOBJECT> GetListObject()
	{
		return listObject;
	}
	
	void SetID(int id)
	{
		this->ID = id;
	}


	


};