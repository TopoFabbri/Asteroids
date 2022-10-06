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
	float shadowOffset = 4;

	if (check.checked)
		DrawRectangleRec(check.rec, check.fill);
	else
		DrawRectangleRec(check.rec, check.empty);

	DrawRectangleLinesEx(check.rec, 3, check.out);
	DrawText(check.txt, (int)(check.rec.x + check.rec.width + 10 + shadowOffset), (int)(check.rec.y + shadowOffset), 30, BLACK);
	DrawText(check.txt, (int)(check.rec.x + check.rec.width + 10), (int)check.rec.y, 30, WHITE);

	if (CheckCollisionPointRec(GetMousePosition(), check.rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		check.checked = !check.checked;
	}
}