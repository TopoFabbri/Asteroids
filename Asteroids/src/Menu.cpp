#include "Menu.h"

Menu createMenu()
{
	Menu menu{};

	menu.isActive = false;
	menu.title = "Menu";
	menu.titlePos = { 0, 0 };
	for (int i = 0; i < menu.btnQty; i++)
	{
		menu.btn[i] = createButton();
	}

	for (int i = 0; i < menu.chkBxQty; i++)
	{
		menu.chbxs[i] = createCheckbox();
	}

	return menu;
}

void mainMenu(Settings& gSettings, Menu& mMenu)
{
	if (!mMenu.isActive)
	{
		TakeScreenshot("PauseScreen.png");
		mMenu.bg = LoadTextureFromImage(LoadImage("PauseScreen.png"));
		mMenu.title = "Main Menu";
		mMenu.isActive = true;
		mMenu.btn[0].text = "Play";
		mMenu.btn[1].text = "Exit";
		mMenu.btn[2].text = "Settings";
		mMenu.btn[3].text = "Controls";
		mMenu.btn[4].text = "Credits";
	}

	// Update
	positionTitle(mMenu);
	takeInput(mMenu, gSettings);
	updateButtons(mMenu);

	// draw
	draw(mMenu);
}

void draw(Menu menu)
{
	Rectangle screen = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };
	BeginDrawing();

	ClearBackground(BLACK);
	DrawTexture(menu.bg, 0, 0, WHITE);

	DrawText(menu.title, (int)menu.titlePos.x, (int)menu.titlePos.y, 50, WHITE);
	drawButton(menu.btn[0]);
	drawButton(menu.btn[1]);
	drawButton(menu.btn[2]);
	drawButton(menu.btn[3]);
	drawButton(menu.btn[4]);

	EndDrawing();
}

void positionTitle(Menu& menu)
{
	menu.titlePos.x = (float)MeasureText(menu.title, 50);
	menu.titlePos.x = (float)GetScreenWidth() / 2 - menu.titlePos.x / 2;
	menu.titlePos.y = (float)GetScreenHeight() / 8;
}

void takeInput(Menu& menu, Settings& gSettings)
{
	if (isButtonPressed(menu.btn[3]))
		gSettings.scene = Scene::ControlsMenu;

	if (isButtonPressed(menu.btn[1]))
		gSettings.scene = Scene::Exit;

	if (isButtonPressed(menu.btn[2]))
		gSettings.scene = Scene::SettingsMenu;

	if (isButtonPressed(menu.btn[4]))
		gSettings.scene = Scene::Credits;

	if (isButtonPressed(menu.btn[0]))
	{
		gSettings.scene = Scene::Game;
		menu.isActive = false;
	}
}

void updateButtons(Menu& menu)
{
	const float btnSpacing = 0.0f;

	updateButton(menu.btn[0], ((float)GetScreenHeight() / 8) * 4);
	updateButton(menu.btn[1], (float)GetScreenHeight() - (float)GetScreenHeight() / 8);
	updateButton(menu.btn[2], menu.btn[0].rec.y + menu.btn[0].rec.height + btnSpacing);
	updateButton(menu.btn[3], menu.btn[2].rec.y + menu.btn[2].rec.height + btnSpacing);
	updateButton(menu.btn[4], menu.btn[3].rec.y + menu.btn[3].rec.height + btnSpacing);
}

void updateButton(Button& btn, float posY)
{
	btn.rec.y = posY;
	btn.rec.x = ((float)GetScreenWidth() / 4);
}

void controlsMenu(Settings& gSettings, Menu& ui)
{
	Vector2 popInd{ (float)GetScreenWidth() / 8, (float)GetScreenHeight() / 8 };
	Rectangle backImage{ popInd.x, popInd.y,
		6 * popInd.x, 6 * popInd.y };

	if (!ui.isActive)
	{
		ui.title = "Controls";
		ui.isActive = true;
		ui.btn[1].text = "Back";
	}

	// Update
	controlsMenuUpdate(ui, gSettings);

	// Draw
	BeginDrawing();

	DrawRectangleRec(backImage, BLACK);

	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
	drawButton(ui.btn[1]);
	DrawText("Player 1", 300, 200, 75, DARKGRAY);
	DrawText("Player 2", GetScreenWidth() - 650, 200, 75, RED);
	DrawRectangle(350, 300, 50, 50, GRAY);
	DrawRectangle(350, 360, 50, 50, GRAY);
	DrawRectangle(GetScreenWidth() - 600, 300, 50, 50, GRAY);
	DrawRectangle(GetScreenWidth() - 600, 360, 50, 50, GRAY);
	DrawText("W", 355, 300, 50, BLACK);
	DrawText("S", 355, 360, 50, BLACK);
	DrawText("^", GetScreenWidth() - 590, 300, 50, BLACK);
	DrawText("v", GetScreenWidth() - 590, 360, 50, BLACK);
	DrawText("Move up", 410, 300, 50, GRAY);
	DrawText("Move down", 410, 360, 50, GRAY);
	DrawText("Move up", GetScreenWidth() - 540, 300, 50, GRAY);
	DrawText("Move down", GetScreenWidth() - 540, 360, 50, GRAY);
	DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2, 200, 50, GRAY);
	DrawText("Menu", GetScreenWidth() / 2 - 90, GetScreenHeight() / 2, 50, RAYWHITE);

	EndDrawing();
}

void controlsMenuUpdate(Menu& ui, Settings& gSettings)
{
	positionTitle(ui);
	updateButtons(ui);

	if (isButtonPressed(ui.btn[1]))
	{
		ui.isActive = false;
		gSettings.scene = Scene::MainMenu;
	}
}

void settingsMenu(Settings& gSettings, Menu& ui)
{
	Vector2 popInd{ (float)GetScreenWidth() / 8, (float)GetScreenHeight() / 8 };
	const Rectangle backImage{ popInd.x, popInd.y,
		6 * popInd.x, 6 * popInd.y };

	if (!ui.isActive)
	{
		ui.title = "Settings";
		ui.isActive = true;
		ui.btn[1].text = "Back";
	}

	// Update
	if (WindowShouldClose())
		CloseWindow();
	if (isButtonPressed(ui.btn[1]))
	{
		ui.isActive = false;
		gSettings.scene = Scene::MainMenu;
	}

	positionTitle(ui);
	updateButtons(ui);

	ui.chbxs[0].rec.x = 300;
	ui.chbxs[0].rec.y = 300;

	ui.chbxs[0].txt = "Show FPS";

	if (ui.chbxs[0].checked)
		gSettings.drawFps = true;
	else
		gSettings.drawFps = false;


	// Draw
	BeginDrawing();

	DrawRectangleRec(backImage, BLACK);
	drawButton(ui.btn[1]);
	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
	drawCheckbox(ui.chbxs[0]);

	EndDrawing();
}

void creditsMenu(Settings& gSettings, Menu& ui)
{
	if (!ui.isActive)
	{
		ui.title = "Credits";
		ui.isActive = true;
		ui.btn[1].text = "Back";
	}

	// Update
	positionTitle(ui);
	updateButtons(ui);

	if (isButtonPressed(ui.btn[1]))
		gSettings.scene = Scene::MainMenu;

	// Draw
	BeginDrawing();

	ClearBackground(BLACK);

	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
	drawButton(ui.btn[1]);
	DrawText("Mateo Fabbri", GetScreenWidth() / 2 - MeasureText("Mateo Fabbri", 50) / 2, GetScreenHeight() / 2, 50, WHITE);

	EndDrawing();
}