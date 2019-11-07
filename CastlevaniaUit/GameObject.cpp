#include "Game.h"
#include"GameObject.h"



void CGameObject::RenderBoundingBox()
{
	
	LPDIRECT3DTEXTURE9 bbox = CTextureDatabase::GetInstance()->GetTexture(BBOX);

	float x, y, framew, frameh;

	GetBoundingBox(x, y, framew, frameh);
	LPSPRITE boundingbox = new CSprite(BBOX, 0,1 );
	boundingbox->Settexture(bbox);
	boundingbox->SetFrameWH((int)framew, (int)frameh);
	boundingbox->Draw(x, y,D3DCOLOR_ARGB(128,255,255,255));
	
}


void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects )
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);
	sr += sl;
	sb += st;

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);
	mr += ml;
	mb += mt;

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		
		if (dynamic_cast<CSimon*>(this))
		{

			if(dynamic_cast<CCandle *>(coObjects->at(i))|| dynamic_cast<CDagger *>(coObjects->at(i)))
				continue;
		}
		else if (dynamic_cast<CEnemy *>(this))
		{
			if (dynamic_cast<CCandle *>(coObjects->at(i)) || dynamic_cast<CItem *>(coObjects->at(i))|| dynamic_cast<CEnemy *>(coObjects->at(i)))
				continue;
		}
		else if(dynamic_cast<CDagger *>(this))
		{
			if (((dynamic_cast<CCandle *>(coObjects->at(i))) || dynamic_cast<CItem *>(coObjects->at(i))) && (/*coObjects->at(i)->isColiable == false||*/ !coObjects->at(i)->isIncamera))
				continue;
		}
		else if (dynamic_cast<CItem *>(this))
		{
			if(!dynamic_cast<CBrick*>(coObjects->at(i)))
				continue;
		}
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}
