#include"Axe.h"
#include"EffectDatabase.h"
CAxe::CAxe()
{
	animation = new CAnimation(100);
	animation->Add(WEAPON, 27);
	animation->Add(WEAPON, 28);
	animation->Add(WEAPON, 29);
	animation->Add(WEAPON, 30);
	vy = AXE_SPEED_Y;
	this->WeaponType = AXE;
	this->IsDead = false;
	this->isIncamera = true;

}


void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (this->IsDead == false)
	{
		vy += GAME_GRAVITY * dt;
		

		CGameObject::Update(dt);

		vx = nx * AXE_SPEED_X;
		SetCollisonWithObject(colliable_objects);


	}
	
}

void CAxe::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	framew = 30;
	frameh = 28;

}
void CAxe::Render()
{
	animation->Render(x, y, default_color);
	RenderBoundingBox();
}
