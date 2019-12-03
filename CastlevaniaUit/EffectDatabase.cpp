#include"EffectDatabase.h"


CEffectDatabase * CEffectDatabase::instance = NULL;

CEffectDatabase* CEffectDatabase::GetInstance()
{
	if (instance == NULL)
		instance = new CEffectDatabase();
	return instance;
}