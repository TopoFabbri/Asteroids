#pragma once

#include <raylib.h>

struct CheckBox
{
	const char* txt;
	Rectangle rec;
	bool checked;
	Color out;
	Color empty;
	Color fill;
};

CheckBox createCheckbox();
void drawCheckbox(CheckBox& check);