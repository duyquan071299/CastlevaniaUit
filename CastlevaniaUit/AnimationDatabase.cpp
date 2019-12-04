#include"AnimationDatabase.h"
CAnimationDatabase * CAnimationDatabase::instance = NULL;

CAnimationDatabase * CAnimationDatabase::GetInstance()
{
	if (instance == NULL) instance = new CAnimationDatabase();
	return instance;
}

void CAnimationDatabase::Add(AniType type,unordered_map<State, LPANIMATION> temp)
{
	
	animations[type] = temp;
}

LPANIMATION CAnimationDatabase::Get(AniType type, State ObjectState)
{
	return (animations[type])[ObjectState];
}
void CAnimationDatabase::LoadAnimation()
{
	CSpriteDatabase* sprites = CSpriteDatabase::GetInstance();
	string object;
	int AnType,Amount,Defaulttime, NumberOfFrame,GraphType,Index,Time,state;
	LPANIMATION ani;
	ifstream ifs("Resources\\Texts\\Animation.txt");
	if (ifs.is_open()) {
		while (ifs.good()) {
			ifs >> AnType >> Amount;
			unordered_map<State, LPANIMATION> temp;
			for (int i = 0; i < Amount; i++)
			{
				ifs >> Defaulttime >> NumberOfFrame >> state;
				ani = new CAnimation(Defaulttime);
				for (int j = 0; j < NumberOfFrame; j++)
				{
					ifs >> GraphType >> Index >> Time;
					ani->Add(static_cast<GraphicType>(GraphType), Index, Time);
					temp[static_cast<State>(state)] = ani;
					Add(static_cast<AniType>(AnType),temp);

				}
			}
			
		}
	}

}