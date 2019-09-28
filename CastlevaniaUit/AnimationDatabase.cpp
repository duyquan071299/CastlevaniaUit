#include"AnimationDatabase.h"
CAnimationDatabase * CAnimationDatabase::instance = NULL;

CAnimationDatabase * CAnimationDatabase::GetInstance()
{
	if (instance == NULL) instance = new CAnimationDatabase();
	return instance;
}

void CAnimationDatabase::Add(GraphicType type, LPANIMATION ani)
{
	animations[type] = ani;
}

LPANIMATION CAnimationDatabase::Get(GraphicType type)
{
	return animations[type];
}