#include"Item.h"

CItem::CItem()
{
	LPANIMATION ani = new CAnimation(100);
	ani->Add(ITEM, 0);
	animation = ani;
}
CItem::CItem(HolderType type)
{
	LPANIMATION ani = new CAnimation(100);
	ani->Add(ITEM, type);
	this->HDType = type;
	animation= ani;
}

void CItem::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	
	switch (this->HDType)
	{
	case HEART:
		framew = frameh = 16;
		break;
	case WHIP:case CROSS:case HOLYWATER:case WATCH:
		framew = frameh = 32;
		break;
	case LARGE_HEART:
		framew = 24;
		frameh = 20;
		break;
	case MONEY_1:case MONEY_2:case MONEY_3:
		framew = frameh = 30;
		break;
	case DAGGER:
		framew = 32;
		frameh = 18;
		break;
	case POTION:
		framew = 26;
		frameh = 32;
		break;
	case CHEST_1:case CHEST_2:case CHICKEN:
		framew = 32;
		frameh = 24;
		break;

	}
}
void CItem::Render()
{	
	animation->Render(x, y, default_color);
	RenderBoundingBox();
	
}
void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	CGameObject::Update(dt);
	
	
	if (!this->HDType == HEART)
		vy += GAME_GRAVITY * dt;
	else
	{
		vy += 0.0002* dt;
	}
		

	if (GetTickCount() - lifetime > ITEM_LIFE_TIME)
	{
		this->IsDead = true;
		return;

	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	// turn off collision when die 
	//if (currentstate->GetStateName() != MARIO_STATE_DIE)
	CalcPotentialCollisions(colliable_objects, coEvents);
	if (coEvents.size() == 0)
	{

		if (this->HDType == HEART && !isOnGround)
		{
			y += dy;
			x += -1.5*sin(y / 17);
		}
		else
		{
			x += dx;
			y += dy;
		}
		
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		isOnGround = true;
	}
	
}