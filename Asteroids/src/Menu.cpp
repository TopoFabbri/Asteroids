#include "Menu.h"

Menu createMenu()
{
	Menu menu{};

	menu.isActive = false;
	menu.title = "Menu";
	menu.titlePos = { 0, 0 };
	menu.btnQty = menu.maxBtns;
	menu.chkBxQty = menu.maxChkBxs;
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
		mMenu.title = "Main Menu";
		mMenu.isActive = true;
		mMenu.btn[0].text = "Play";
		mMenu.btn[1].text = "Exit";
		mMenu.btn[2].text = "Settings";
		mMenu.btn[3].text = "Controls";
		mMenu.btn[4].text = "Credits";
		mMenu.bg = LoadTexture("res/bgs/backgroundMenu.png");
		mMenu.window = LoadTexture("res/ui/Window.png");
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
	Rectangle bgSource{ 0, 0, (float)menu.bg.width, (float)menu.bg.height };
	Rectangle screen{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };

	Rectangle wdSource{ 0, 0, (float)menu.window.width, (float)menu.window.height };
	Rectangle wdDest{ 0, 0, (float)GetScreenWidth() * (2.f / 3.f), (float)GetScreenHeight() * (19.f / 20.f) };

	wdDest.x = (float)GetScreenWidth() / 2 - wdDest.width / 2;
	wdDest.y = (float)GetScreenHeight() / 2 - wdDest.height / 2;

	BeginDrawing();

	ClearBackground(BLACK);
	DrawTexturePro(menu.bg, bgSource, screen, { 0, 0 }, 0, WHITE);
	DrawTexturePro(menu.window, wdSource, wdDest, { 0, 0 }, 0, WHITE);

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
	menu.titlePos.y = (float)GetScreenHeight() * (9.f / 64.f);
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
	const float btnSpacing = 10.0f;

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
	if (!ui.isActive)
	{
		ui.title = "Controls";
		ui.isActive = true;
		ui.btn[1].text = "Back";
		ui.bg = LoadTexture("res/bgs/backgroundMenu.png");
		ui.window = LoadTexture("res/ui/Window.png");

		for (int i = 0; i < ui.maxAnims; i++)
		{
			ui.anim[i] = {};
		}

		ui.anim[0] = newAnimation("res/anims/MovementAnim.png", 44);
	}

	// Update
	controlsMenuUpdate(ui, gSettings);

	// Draw
	Rectangle source{ 0, 0, (float)ui.bg.width, (float)ui.bg.height };
	Rectangle dest{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };

	Rectangle wdSource{ 0, 0, (float)ui.window.width, (float)ui.window.height };
	Rectangle wdDest{ 0, 0, (float)GetScreenWidth() * (2.f / 3.f), (float)GetScreenHeight() * (19.f / 20.f) };

	wdDest.x = (float)GetScreenWidth() / 2 - wdDest.width / 2;
	wdDest.y = (float)GetScreenHeight() / 2 - wdDest.height / 2;

	BeginDrawing();
	DrawTexturePro(ui.bg, source, dest, { 0, 0 }, 0, WHITE);
	DrawTexturePro(ui.window, wdSource, wdDest, { 0, 0 }, 0, WHITE);
	drawFrame(ui.anim[0], WHITE);

	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
	drawButton(ui.btn[1]);

	EndDrawing();
}

void controlsMenuUpdate(Menu& ui, Settings& gSettings)
{
	positionTitle(ui);
	updateButtons(ui);

	for (int i = 0; i < ui.maxAnims; i++)
	{
		updateAnimation(ui.anim[i]);
	}

	setPos(ui.anim[0], { 0, 0 });
	setSize(ui.anim[0], { 200, 200 });

	if (isButtonPressed(ui.btn[1]))
	{
		ui.isActive = false;
		gSettings.scene = Scene::MainMenu;
	}
}

void settingsMenu(Settings& gSettings, Menu& ui)
{
	if (!ui.isActive)
	{
		ui.title = "Settings";
		ui.isActive = true;
		ui.btn[1].text = "Back";
		ui.chbxs[0].txt = "Show FPS";
		ui.chbxs[1].txt = "Show colliders";
		ui.chbxs[2].txt = "Circle warp";
		ui.bg = LoadTexture("res/bgs/backgroundMenu.png");
		ui.window = LoadTexture("res/ui/Window.png");
		ui.chkBxQty = 3;
		ui.btnQty = 1;
	}

	// Update

	if (isButtonPressed(ui.btn[1]))
	{
		ui.isActive = false;
		gSettings.scene = Scene::MainMenu;
	}

	positionTitle(ui);
	updateButtons(ui);

	for (int i = 0; i < ui.chkBxQty; i++)
	{
		ui.chbxs[i].rec.x = (float)GetScreenWidth() / 4;
		ui.chbxs[i].rec.y = (float)(350 + i * 100);
	}

	// Input

	if (ui.chbxs[0].checked)
		gSettings.drawFps = true;
	else
		gSettings.drawFps = false;

	if (ui.chbxs[1].checked)
		gSettings.showColliders = true;
	else
		gSettings.showColliders = false;

	if (ui.chbxs[2].checked)
		gSettings.circleWarp = true;
	else
		gSettings.circleWarp = false;


	// Draw
	Rectangle source{ 0, 0, (float)ui.bg.width, (float)ui.bg.height };
	Rectangle dest{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };

	Rectangle wdSource{ 0, 0, (float)ui.window.width, (float)ui.window.height };
	Rectangle wdDest{ 0, 0, (float)GetScreenWidth() * (2.f / 3.f), (float)GetScreenHeight() * (19.f / 20.f) };

	wdDest.x = (float)GetScreenWidth() / 2 - wdDest.width / 2;
	wdDest.y = (float)GetScreenHeight() / 2 - wdDest.height / 2;

	BeginDrawing();
	DrawTexturePro(ui.bg, source, dest, { 0, 0 }, 0, WHITE);
	DrawTexturePro(ui.window, wdSource, wdDest, { 0, 0 }, 0, WHITE);

	drawButton(ui.btn[1]);
	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
	for (int i = 0; i < ui.chkBxQty; i++)
	{
		drawCheckbox(ui.chbxs[i]);
	}

	EndDrawing();
}

void creditsMenu(Settings& gSettings, Menu& ui)
{
	Vector2 popInd{ (float)GetScreenWidth() / 8, 0 };
	const Rectangle backImage{ popInd.x, popInd.y,
		6 * popInd.x, (float)GetScreenHeight() };

	const char* credits[6] = { "Programing:", "Topo","", "Art:", "Chia", "Kenney" };
	const Color color[6] = { WHITE, WHITE, BLACK, RED, RED, RED };
	int posY = GetScreenHeight() / 2 - 50 * 3;

	if (!ui.isActive)
	{
		TakeScreenshot("PauseScreen.png");
		ui.bg = LoadTextureFromImage(LoadImage("PauseScreen.png"));
		ui.title = "Credits";
		ui.isActive = true;
		ui.btn[1].text = "Back";
	}

	// Update
	positionTitle(ui);
	updateButtons(ui);

	if (isButtonPressed(ui.btn[1]))
	{
		gSettings.scene = Scene::MainMenu;
		ui.isActive = false;
	}

	// Draw
	BeginDrawing();

	ClearBackground(BLACK);

	DrawTexture(ui.bg, 0, 0, WHITE);
	DrawRectangleRec(backImage, BLACK);
	drawRectangleRecLines(backImage, WHITE);
	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
	drawButton(ui.btn[1]);

	for (int i = 0; i < 6; i++)
	{
		DrawText(credits[i], GetScreenWidth() / 2 - MeasureText(credits[i], 50) / 2, posY, 50, color[i]);
		posY += 50;
	}

	EndDrawing();
}

void pauseMenu(Settings& gSettings, Menu& ui)
{
	Vector2 popInd{ (float)GetScreenWidth() / 8, 0 };
	const Rectangle backImage{ popInd.x, popInd.y,
		6 * popInd.x, (float)GetScreenHeight() };


	if (!ui.isActive)
	{
		TakeScreenshot("PauseScreen.png");
		ui.bg = LoadTextureFromImage(LoadImage("PauseScreen.png"));
		ui.title = "Pause";
		ui.isActive = true;
		ui.btn[1].text = "Main Menu";
		ui.btn[0].text = "Play";
		ui.window = LoadTexture("res/ui/Window.png");
	}

	// Update
	positionTitle(ui);
	updateButtons(ui);

	if (isButtonPressed(ui.btn[1]))
	{
		gSettings.scene = Scene::MainMenu;
		ui.isActive = false;
	}

	if (isButtonPressed(ui.btn[0]) || IsKeyPressed(KEY_ESCAPE))
	{
		gSettings.scene = Scene::Game;
		ui.isActive = false;
	}

	// Draw
	Rectangle wdSource{ 0, 0, (float)ui.window.width, (float)ui.window.height };
	Rectangle wdDest{ 0, 0, (float)GetScreenWidth() * (2.f / 3.f), (float)GetScreenHeight() * (19.f / 20.f) };

	wdDest.x = (float)GetScreenWidth() / 2 - wdDest.width / 2;
	wdDest.y = (float)GetScreenHeight() / 2 - wdDest.height / 2;

	BeginDrawing();

	ClearBackground(BLACK);
	DrawTexture(ui.bg, 0, 0, WHITE);
	DrawRectangleRec(wdDest, { 0, 0, 0, 150 });
	DrawTexturePro(ui.window, wdSource, wdDest, { 0, 0 }, 0, WHITE);

	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
	drawButton(ui.btn[0]);
	drawButton(ui.btn[1]);

	EndDrawing();
}