#include"OutDoorStage.h"


void COutDoorStage::Loadresources()
{
	SetMapBound(0, 1536);
	CScoreBoard::GetInstance()->SetStage("01");
	this->CurrentStageType = OUTDOOR_STAGE;
}
void COutDoorStage::Render()
{
	if ((CSimon::GetInstance()->IsOnAnimation || CSimon::GetInstance()->IsWalkToCastle) && CSimon::GetInstance()->vx > 0)
	{
		DrawHiddenDoor();
	}
}
void COutDoorStage::Update(DWORD dt, CGrid * CurrentGrid)
{
	CCamera::GetInstance()->SetPosition(CSimon::GetInstance()->x - SCREEN_WIDTH / 2 + 40, 0);
	CCamera::GetInstance()->Update(MapBoundLeft, MapBoundRight);

}

void COutDoorStage::DrawHiddenDoor()
{
	HiddenDoor = new CSprite(MAP, 0, 1);
	HiddenDoor->Settexture(CTextureDatabase::GetInstance()->GetTexture(HIDING_OBJECT));
	HiddenDoor->SetFrameWH(96, 128);
	HiddenDoor->Draw((float)1408, (float)240, default_color);
}