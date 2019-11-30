#include"Cell.h"

void CCell::AddObject(LPGAMEOBJECT Object)
{
	auto it = find(listObject.begin(), listObject.end(), Object);
	
	if (it != listObject.end())
	{
		return;
	}
	else
	{
		this->listObject.push_back(Object);
	}
	
}