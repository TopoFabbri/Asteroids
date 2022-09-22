#pragma once

#include <raylib.h>

	struct Button
	{
		Rectangle rec{ 0, 0, 200, 50 };
		Color normal = WHITE;
		Color hovered = DARKGRAY;
		Color txtColor = BLACK;
		float size = 30;
		float txtSpacing = 1;
		const char* text = "Button";
		float indent = 10;
		Font font = GetFontDefault();
	};

	Button createButton();
	void drawButton(Button& btn);
	bool isButtonPressed(Button btn);
