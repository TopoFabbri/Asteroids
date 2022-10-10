#include "Animation.h"

Animation newAnimation(const char* path, int frames, float duration)
{
	Animation anim{};

	anim.sequence = LoadTexture(path);

	anim.frames = frames;
	anim.curFrame = 0;
	anim.frameWidth = (float)anim.sequence.width / (float)frames;
	anim.rot = 0;
	anim.timeElapsed = 0;
	anim.duration = duration;
	anim.drawRectangle = false;

	anim.source = { 0, 0, anim.frameWidth, (float)anim.sequence.height };
	anim.dest = anim.source;
	anim.origin = { 0, 0 };

	return anim;
}

void setPos(Animation& anim, Vector2 pos)
{
	anim.dest.x = pos.x;
	anim.dest.y = pos.y;
}

void setSize(Animation& anim, Vector2 size)
{
	anim.dest.width = size.x;
	anim.dest.height = size.y;
}

void updateAnimation(Animation& anim)
{
	float frameTime = anim.duration / (float)anim.frames;

	anim.timeElapsed += GetFrameTime();

	if (anim.timeElapsed >= frameTime * (float)anim.curFrame)
		anim.curFrame++;

	if (anim.curFrame > anim.frames)
		anim.curFrame = 0;

	if (anim.timeElapsed > anim.duration)
		anim.timeElapsed = 0;

	anim.source = { anim.frameWidth * (float)anim.curFrame, 0,
		anim.frameWidth, (float)anim.sequence.height };
}

void drawFrame(Animation anim, Color tint)
{
	DrawTexturePro(anim.sequence, anim.source, anim.dest, anim.origin,
		anim.rot, tint);

	if (anim.drawRectangle)
	{
		DrawRectangleLines((int)anim.dest.x, (int)anim.dest.y,
			(int)anim.dest.width, (int)anim.dest.height, SKYBLUE);
	}
}