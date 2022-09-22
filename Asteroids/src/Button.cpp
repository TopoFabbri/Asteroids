#include "Button.h"

	void drawButton(Button& btn)
	{
		const Vector2 txtSize = MeasureTextEx(btn.font, btn.text, btn.size, btn.txtSpacing);

		btn.rec.width = txtSize.x + 2 * btn.indent;
		btn.rec.height = txtSize.y;

		const Color printColor = CheckCollisionPointRec(GetMousePosition(), btn.rec) ? btn.hovered : btn.normal;
		DrawRectangleRec(btn.rec, printColor);

		if (CheckCollisionPointRec(GetMousePosition(), btn.rec))
			DrawRectangleLinesEx(btn.rec, 1, RAYWHITE);

		DrawTextEx(btn.font, btn.text, { btn.rec.x + btn.indent, btn.rec.y }, btn.size, btn.txtSpacing, btn.txtColor);
	}

	bool isButtonPressed(Button btn)
	{
		return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			CheckCollisionPointRec(GetMousePosition(), btn.rec));
	}

	Button createButton()
	{
		Button button;

		button.rec = { 0, 0, 200, 50 };
		button.normal = WHITE;
		button.hovered = GRAY;
		button.txtColor = BLACK;
		button.size = 30;
		button.txtSpacing = 1;
		button.text = "Button";
		button.indent = 10;
		button.font = GetFontDefault();

		return button;
	}