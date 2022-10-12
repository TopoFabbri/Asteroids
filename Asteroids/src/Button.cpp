#include "Button.h"

void drawButton(Button& btn)
{
	const Rectangle source{ 0, 0, (float)btn.sprite.width, (float)btn.sprite.height };

	if (CheckCollisionPointRec(GetMousePosition(), btn.rec))
		DrawTexturePro(btn.sprite, source, btn.rec, { 0, 0 }, 0, btn.hovered);
	else
		DrawTexturePro(btn.sprite, source, btn.rec, { 0, 0 }, 0, btn.normal);

	DrawTextEx(btn.font, btn.text, { btn.rec.x + btn.indent, btn.rec.y + btn.indent },
		btn.size, btn.txtSpacing, btn.txtColor);
}

bool isButtonPressed(Button btn)
{
	return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
		CheckCollisionPointRec(GetMousePosition(), btn.rec));
}

Button createButton()
{
	Button button{};

	button.rec = { 0, 0, 200, 50 };
	button.normal = WHITE;
	button.hovered = GREEN;
	button.txtColor = WHITE;
	button.sprite = LoadTexture("res/ui/Button.png");
	button.size = 30;
	button.txtSpacing = 1;
	button.text = "Button";
	button.indent = 10;
	button.font = GetFontDefault();

	return button;
}

void updateButton(Button& btn)
{
	btn.size = (float)GetScreenWidth() * (1.f / 64.f);

	const Vector2 txtSize = MeasureTextEx(btn.font, btn.text, btn.size, btn.txtSpacing);

	btn.rec.width = txtSize.x + 2 * btn.indent;
	btn.rec.height = txtSize.y + 2 * btn.indent;
}