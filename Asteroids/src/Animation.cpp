#include "Animation.h"

Animation newAnimation(const char* path, int frames)
{
	Animation anim{};

	anim.sequence = LoadTexture(path);

	anim.frames = frames;
	anim.curFrame = 0;
	anim.frameWidth = (float)anim.sequence.width / (float)frames;
	anim.rot = 0;

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
	anim.curFrame++;

	if (anim.curFrame > anim.frames)
		anim.curFrame = 0;

	anim.source = { anim.frameWidth * (float)anim.curFrame, 0,
		anim.frameWidth, (float)anim.sequence.height };
}

void drawFrame(Animation anim, Color tint)
{
	DrawTexturePro(anim.sequence, anim.source, anim.dest, anim.origin,
		anim.rot, tint);

	DrawRectangleLines((int)anim.dest.x, (int)anim.dest.y, 
		(int)anim.dest.width, (int)anim.dest.height, SKYBLUE);
}