#pragma once
#include"GameObject.h"
#include"BrokenBrickEffect.h"
#include"BubbleEffect.h"
#include"DestroyEffect.h"

class CEffectDatabase
{
private:
	static CEffectDatabase* instance;

	vector<CEffect*> listEffect;
public:
	float x, y;
	static CEffectDatabase* GetInstance();
	CEffectDatabase() {};
	void AddBrokenBrickEffect(float x, float y)
	{
		listEffect.push_back(new CBrokenBrickEffect(x, y, -0.15f, -0.25f));
		listEffect.push_back(new CBrokenBrickEffect(x, y, 0.15f, -0.2f));
		listEffect.push_back(new CBrokenBrickEffect(x, y, -0.07f, -0.22f));
		listEffect.push_back(new CBrokenBrickEffect(x, y, 0.1f, -0.3f));
	}
	void AddBubbleEffect(float x, float y)
	{
		listEffect.push_back(new CBubbleEffect(x-16, y,-0.02f, -0.3f));
		listEffect.push_back(new CBubbleEffect(x, y,0.0f, -0.5f));
		listEffect.push_back(new CBubbleEffect(x+8, y, 0.02f, -0.3f));
	}
	void AddHitEffect(float x, float y)
	{
		listEffect.push_back(new CDestroyEffect(x , y, 2));
	}
	void AddBurnEffect(float x, float y)
	{
		listEffect.push_back(new CDestroyEffect(x, y, 1));
	}
	vector<CEffect*> GetListEffect()
	{
		return listEffect;
	}
	void RemoveForListEffect(int index)
	{
		listEffect.erase(listEffect.begin() + index);
	}

};

