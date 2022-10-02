#pragma once

#include <raylib.h>

	struct Button
	{
		Rectangle rec;
		Color normal;
		Color hovered;
		Color txtColor;
		Texture2D sprite;
		float size;
		float txtSpacing;
		const char* text;
		float indent;
		Font font;
	};

	Button createButton();
	void drawButton(Button& btn);
	bool isButtonPressed(Button btn);
