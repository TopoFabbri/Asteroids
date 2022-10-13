#include "Cursor.h"

Cursor newCursor()
{
	Cursor cur{};

	cur.state = Cursor::Idle;
	cur.pos = GetMousePosition();
	cur.size = { (float)GetScreenWidth() * (7.f / 384.f), (float)GetScreenWidth() * (7.f / 384.f) };
	cur.idle = LoadTexture("res/ui/CursorMenuIdle.png");
	cur.hover = LoadTexture("res/ui/CursorMenuHover.png");

	return cur;
}

void updateCursor(Cursor& cur)
{
	cur.pos = GetMousePosition();

	switch (cur.state)
	{
	case Cursor::Idle:
		cur.sprite = cur.idle;
		break;

	case Cursor::Hover:
		cur.sprite = cur.hover;
		break;

	case Cursor::Move:
		cur.sprite = cur.move;
		break;

	case Cursor::Fire:
		cur.sprite = cur.fire;
		break;

	default:;
	}


}

void drawCursor(Cursor cur)
{
	Rectangle source{ 0, 0, 250, 250 };
	Rectangle dest{ cur.pos.x, cur.pos.y, cur.size.x, cur.size.y };

	DrawTexturePro(cur.sprite, source, dest, { 0, 0 }, 0, WHITE);
}

bool isHovering(Cursor cur, Rectangle rec)
{
	bool hovering = CheckCollisionPointRec(cur.pos, rec);
	return hovering;
}