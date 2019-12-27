#include"ScoreBoard.h"
#include"Camera.h"
#include"Simon.h"
#include"StageManager.h"

CScoreBoard * CScoreBoard::instance = NULL;
#define SPACING 15.0f
#define SPACING_HEAL 11.0f
#define POS_X_1 400.0f
#define POS_X_2 460.0f
#define POS_X_3 100.0f
#define POS_X_4 300.0f
#define POS_X_5 315.0f
#define POS_X_6 109.0f
#define POS_Y_1 34.0f
#define POS_Y_2 52.0f
#define POS_Y_3 14.0f
#define POS_Y_4 32.0f
#define POS_Y_5 50.0f



CScoreBoard* CScoreBoard::GetInstance()
{
	if (!instance)
		instance = new CScoreBoard();
	return instance;
}

CScoreBoard::CScoreBoard()
{
	SetUp(0.0f,0.0f);
}
CScoreBoard::~CScoreBoard()
{
	instance = NULL;
}
void CScoreBoard::SetUp(float x, float y)
{
	this->x = x;
	this->y = y;
	this->ClearBoard = CSpriteDatabase::GetInstance()->GetSprite(SCORE_BOARD,0);
	this->ClearBoard->Settexture(CTextureDatabase::GetInstance()->GetTexture(SCORE_BOARD));
	this->Stage = "01";
	this->Heart = "00";
	this->Life = "00";
	this->Score = "000000";
	this->Time = "0300";
	this->SimonHeal = 16;
	this->BossHeal = 16;
	
}
void CScoreBoard::Render()
{
	ClearBoard->DrawScoreBoard(x, y, default_color	);
	for (int i = 0; i < this->Heart.length(); i++)
	{
		
		CSpriteDatabase::GetInstance()->GetSprite(FONT, (int)this->Heart.at(i) - 48)->DrawScoreBoard(this->x + POS_X_1 + i * SPACING, this->y + POS_Y_1, default_color);
		
	}
	for (int i = 0; i < this->Life.length(); i++)
	{
		CSpriteDatabase::GetInstance()->GetSprite(FONT, (int)this->Life.at(i) - 48)->DrawScoreBoard(this->x + POS_X_1 + i * SPACING, this->y+ POS_Y_2, default_color);
		
	}
	for (int i = 0; i < this->Stage.length(); i++)
	{
		CSpriteDatabase::GetInstance()->GetSprite(FONT, (int)this->Stage.at(i) - 48)->DrawScoreBoard(this->x + POS_X_2 + i* SPACING, this->y+ POS_Y_3, default_color);

	}
	for (int i = 0; i < this->Score.length(); i++)
	{
		CSpriteDatabase::GetInstance()->GetSprite(FONT, (int)this->Score.at(i) - 48)->DrawScoreBoard(this->x + POS_X_3 + i* SPACING, this->y + POS_Y_3, default_color);

	}
	for (int i = 0; i < this->Time.length(); i++)
	{
		CSpriteDatabase::GetInstance()->GetSprite(FONT, (int)this->Time.at(i) - 48)->DrawScoreBoard(this->x + POS_X_4 + i* SPACING, this->y + POS_Y_3, default_color);

	}
	for (int i = 0; i < this->Heart.length(); i++)
	{

		CSpriteDatabase::GetInstance()->GetSprite(FONT, (int)this->Heart.at(i) - 48)->DrawScoreBoard(this->x + POS_X_1 + i * SPACING, this->y + POS_Y_1, default_color);

	}
	for (int i = 0; i < this->SimonHeal; i++)
	{
		CSpriteDatabase::GetInstance()->GetSprite(HEAL, 0)->DrawScoreBoard(this->x + POS_X_6+ i*SPACING_HEAL, this->y + POS_Y_4-1, default_color);

	}
	for (int i = 0; i < this->BossHeal; i++)
	{
		CSpriteDatabase::GetInstance()->GetSprite(HEAL,2)->DrawScoreBoard(this->x + POS_X_6 + i * SPACING_HEAL, this->y + POS_Y_5, default_color);

	}
	if(CSimon::GetInstance()->WeaponType>0)
		CSpriteDatabase::GetInstance()->GetSprite(ITEM, CSimon::GetInstance()->WeaponType)->DrawScoreBoard(this->x + POS_X_5, this->y + POS_Y_4, default_color);

	if(CSimon::GetInstance()->WeaponShot==2)
		CSpriteDatabase::GetInstance()->GetSprite(ITEM, DOUBLE_SHOT)->DrawScoreBoard(this->x + 450.0f , this->y + POS_Y_1, default_color);

		
}
void CScoreBoard::Update()
{
	char buffer[256];
	sprintf(buffer, "%02d", CSimon::GetInstance()->Heart);
	this->Heart = buffer;
	sprintf(buffer, "%02d", CSimon::GetInstance()->Life);
	this->Life = buffer;
	sprintf(buffer, "%06d", CSimon::GetInstance()->Score);
	this->Score = buffer;
	sprintf(buffer, "%04d", CSimon::GetInstance()->LifeTime);
	this->Time = buffer;
	this->SimonHeal = CSimon::GetInstance()->Heal;

}
