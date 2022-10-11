#pragma once
#include <raylib.h>

struct Cursor
{
	enum State
	{
		Idle,
		Hover,
		Move,
		Fire
	};

	State state;
	Vector2 pos;
	Vector2 size;

	Texture2D sprite;
	Texture2D idle;
	Texture2D hover;
	Texture2D move;
	Texture2D fire;
};

Cursor newCursor();
void updateCursor(Cursor& cur);
void drawCursor(Cursor cur);
bool isHovering(Cursor cur, Rectangle rec);