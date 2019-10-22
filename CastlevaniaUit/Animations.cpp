#include"Animations.h"

void CAnimation::Add(GraphicType type,int index,DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;
	LPSPRITE sprite = CSpriteDatabase::GetInstance()->GetSprite(type,index);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y,  D3DCOLOR color)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			isLastFrame = false;
			if (currentFrame == frames.size())
			{
				currentFrame = 0;
				isLastFrame = true;

			}
			else
			{
				//t += now - lastFrameTime;
				isLastFrame = false;
			}
		}

	}
	frames[currentFrame]->GetSprite()->Draw(x, y, color);
}