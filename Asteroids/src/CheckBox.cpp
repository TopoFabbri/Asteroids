#include "CheckBox.h"

CheckBox createCheckbox()
{
	CheckBox cb{};

	cb.rec = { 0, 0, 25, 25 };
	cb.checked = false;
	cb.out = LIGHTGRAY;
	cb.empty = RAYWHITE;
	cb.fill = DARKGRAY;
	cb.txt = "Checkbox";

	return cb;
}

void drawCheckbox(CheckBox& check)
{
	float shadowOffset = (float)GetScreenWidth() * (1.f/480.f);
	check.rec.width = (float)GetScreenWidth() * (5.f / 384.f);
	check.rec.height = (float)GetScreenWidth() * (5.f / 384.f);

	if (check.checked)
		DrawRectangleRec(check.rec, check.fill);
	else
		DrawRectangleRec(check.rec, check.empty);

	DrawRectangleLinesEx(check.rec, 3, check.out);
	DrawText(check.txt, (int)(check.rec.x + check.rec.width + 10 + shadowOffset),
		(int)(check.rec.y + shadowOffset),	
		(int)((float)GetScreenWidth() * (1.f/64.f)), BLACK);
	DrawText(check.txt, (int)(check.rec.x + check.rec.width + 10), (int)check.rec.y, (int)((float)GetScreenWidth() * (1.f / 64.f)), WHITE);

	if (CheckCollisionPointRec(GetMousePosition(), check.rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		check.checked = !check.checked;
	}
}