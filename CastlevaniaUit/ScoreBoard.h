#pragma once
#include"GameObject.h"
#include"ScoreBoard.h"
class CScoreBoard
{
private:
	static CScoreBoard* instance;
	
	LPSPRITE ClearBoard;
	string Score;
	string Stage;
	string Time;
	string Life;
	string Heart;
	int SimonHeal;
	int BossHeal;
	
public:
	float x, y;
	static CScoreBoard* GetInstance();
	void SetBossHeal(int heal)
	{
		this->BossHeal = heal;
	}
	CScoreBoard();
	CScoreBoard(float x, float y);
	void Render();
	void Update();


};

