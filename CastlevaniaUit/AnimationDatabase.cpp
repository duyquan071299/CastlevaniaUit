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
void CAnimationDatabase::LoadAnimation()
{
	CSpriteDatabase* sprites = CSpriteDatabase::GetInstance();
	string object;
	int Animationtype, Defaulttime, NumberOfFrame,Type,Index,Time;
	LPANIMATION ani;
	ifstream ifs("Resources\\Texts\\Animation.txt");
	if (ifs.is_open()) {
		while (ifs.good()) {
			ifs >> Animationtype >> Defaulttime>> NumberOfFrame;
			for (int i = 0; i < NumberOfFrame; i++)
			{
				ifs >> Type >> Index >> Time;
				ani = new CAnimation(Defaulttime);
				ani->Add(static_cast<GraphicType>(Type), Index,Time);
				animations[static_cast<GraphicType>(Type)] = ani;

			}
		}
	}
}