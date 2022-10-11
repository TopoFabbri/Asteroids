#pragma once
#include "Button.h"
#include "CheckBox.h"
#include "Settings.h"
#include "Animation.h"
#include "Cursor.h"
#include "Topo.h"

struct Menu
{
	static const int maxBtns = 10;
	static const int maxChkBxs = 10;
	static const int maxAnims = 10;

	int btnQty;
	int chkBxQty;
	Texture2D bg;
	Texture2D window;
	bool isActive;
	const char* title;
	Vector2 titlePos;
	Cursor cur;
	Button btn[maxBtns];
	CheckBox chbxs[maxChkBxs];
	Animation anim[maxAnims];
};

Menu createMenu();
void mainMenu(Settings& gSettings, Menu& mMenu);
void draw(Menu menu);
void positionTitle(Menu& menu);
void takeInput(Menu& menu, Settings& gSettings);
void updateButtons(Menu& menu);
void positionButton(Button& btn, float posY);
void controlsMenu(Settings& gSettings, Menu& ui);
void controlsMenuUpdate(Menu& ui, Settings& gSettings);
void settingsMenu(Settings& gSettings, Menu& ui);
void creditsMenu(Settings& gSettings, Menu& ui);
void pauseMenu(Settings& gSettings, Menu& ui);