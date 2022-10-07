#pragma once

#include <raylib.h>

struct Animation
{
	int frames;
	int curFrame;
	float frameWidth;
	float rot;

	Texture2D sequence;
	Rectangle source;
	Rectangle dest;
	Vector2 origin;
};

Animation newAnimation(const char* path, int frames);
void setPos(Animation& anim, Vector2 pos);
void setSize(Animation& anim, Vector2 size);
void updateAnimation(Animation& anim);
void drawFrame(Animation anim, Color tint);