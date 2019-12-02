#include"Door.h"


CDoor::CDoor(float x, float y)
{
	this->x = x;
	this->y = y;
	LPANIMATION ani = new CAnimation(100);
	ani->Add(DOOR, 1);
	animations[CLOSE] = ani;

	ani = new CAnimation(100);
	ani->Add(DOOR, 2);
	animations[OPEN] = ani;

	ani = new CAnimation(1000);
	ani->Add(DOOR, 1);
	ani->Add(DOOR, 0);
	ani->Add(DOOR, 2);
	animations[OPENNING] = ani;

	ani = new CAnimation(1000);
	ani->Add(DOOR, 2);
	ani->Add(DOOR, 0);
	ani->Add(DOOR, 1);
	animations[CLOSING] = ani;



	currentstate = CLOSE;
	curAnimation = animations[currentstate];

	
}