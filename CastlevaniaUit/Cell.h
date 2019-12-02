#pragma once
#include "GameObject.h"

class CCell
{
private:
	int ID;
	vector<LPGAMEOBJECT> listObject;
public:
	CCell() {};
	~CCell() { listObject.clear(); };
	void AddObject(LPGAMEOBJECT Object);
	int GetID() {
		return ID;
	}

	vector<LPGAMEOBJECT> GetListObject()
	{
		//if(listObject!=NU::)
		return listObject;
	}
	
	void SetID(int id)
	{
		this->ID = id;
	}


	void RemoveObject(LPGAMEOBJECT obj)
	{
		listObject.erase(remove(listObject.begin(), listObject.end(), obj), listObject.end());
	}


};