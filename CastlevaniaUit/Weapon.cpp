#include"Weapon.h"
#include"Simon.h"
#include"BatBoss.h"

void CWeapon::SetCollisonWithObject(vector<LPGAMEOBJECT> *coObjects )
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEOBJECT> ListObject;
	ListObject.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (!dynamic_cast<CBrick *>(coObjects->at(i)))
		{
			ListObject.push_back(coObjects->at(i));
		}
	coEvents.clear();

	CalcPotentialCollisions(&ListObject, coEvents);

	

		x += dx;
		y += dy;

	
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		
	
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CCandle *>(e->obj))
			{
				isColiableWithObject = true;
				dynamic_cast<CCandle *>(e->obj)->ChangeAnimation();


			}
			else if (dynamic_cast<CEnemy*>(e->obj))
			{
				CEffectDatabase::GetInstance()->AddHitEffect(e->obj->x, e->obj->y);
				isColiableWithObject = true;
				if (dynamic_cast<CBatBoss*>(e->obj))
				{
				
					dynamic_cast<CBatBoss*>(e->obj)->SetHeal(dynamic_cast<CBatBoss*>(e->obj)->GetHeal() - 1);
	

					continue;
				}
			
				dynamic_cast<CEnemy *>(e->obj)->ChangeAnimation();
				if (dynamic_cast<CGhost*>(e->obj))
					CSimon::GetInstance()->Score += KILL_GHOST_SCORE;
				else if (dynamic_cast<CBat*>(e->obj) || dynamic_cast<CPanther*>(e->obj))
					CSimon::GetInstance()->Score += KILL_BAT_SCORE;
				else if (dynamic_cast<CKappa*>(e->obj))
					CSimon::GetInstance()->Score += KILL_KAPPA_SCORE;
				dynamic_cast<CEnemy*>(e->obj)->ChangeAnimation();


			}
		}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


}