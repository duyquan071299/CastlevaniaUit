#include"Dagger.h"

CDagger::CDagger()
{
	animation = new CAnimation(100);
	this->IsDead = true;

}


void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (this->IsDead==false)
	{
		
		CGameObject::Update(dt);
		
		vx = nx*DAGGER_SPEED * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(colliable_objects, coEvents);

		if (coEvents.size() == 0)
		{
			
			x += dx;

		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			x += min_tx * dx + nx * 0.4f;		
			y += min_ty * dy + ny * 0.4f;

			/*if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;*/
			
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CLargeCandle *>(e->obj))
				{
					this->IsDead = true;
					dynamic_cast<CLargeCandle *>(e->obj)->ChangeAnimation();
				

				}



			}
			
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

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