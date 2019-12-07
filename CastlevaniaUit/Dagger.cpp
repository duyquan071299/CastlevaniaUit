#include"Dagger.h"

CDagger::CDagger()
{
	animation = new CAnimation(100);
	this->IsDead = false;
	WeaponType = DAGGER;
}


void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (this->IsDead==false)
	{

		CGameObject::Update(dt);
		
		vx = nx*DAGGER_SPEED;
		vy = 0;
		SetCollisonWithObject(colliable_objects);
		if (isColiableWithObject==true)
			this->IsDead = true;
		

	}
}
void CDagger::ChangeAnimation(int index)
{
	animation = new CAnimation(100);
	animation->Add(WEAPON, index);
}
void CDagger::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	framew = 32;
	frameh = 18;
}
void CDagger::Render()
{
	animation->Render(x,y, default_color);
	RenderBoundingBox();
}
