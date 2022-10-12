#include "Menu.h"

Menu createMenu()
{
	Menu menu{};

	menu.isActive = false;
	menu.title = "Menu";
	menu.titlePos = { 0, 0 };
	menu.btnQty = menu.maxBtns;
	menu.chkBxQty = menu.maxChkBxs;
	menu.cur = newCursor();
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
		mMenu.cur = newCursor();
	}

	// Update
	positionTitle(mMenu);
	updateButtons(mMenu);
	updateCursor(mMenu.cur);
	takeInput(mMenu, gSettings);

	// draw
	draw(mMenu);
}

void draw(Menu menu)
{
	Rectangle bgSource{ 0, 0, (float)menu.bg.width, (float)menu.bg.height };
	Rectangle bgDest{ -((float)GetScreenHeight() * (16.f / 9.f) - (float)GetScreenWidth())/2, 0, (float)GetScreenHeight() * (16.f / 9.f), (float)GetScreenHeight() };

	Rectangle wdSource{ 0, 0, (float)menu.window.width, (float)menu.window.height };
	Rectangle wdDest{ 0, 0, (float)GetScreenWidth() * (2.f / 3.f), (float)GetScreenHeight() * (19.f / 20.f) };

	wdDest.x = (float)GetScreenWidth() / 2 - wdDest.width / 2;
	wdDest.y = (float)GetScreenHeight() / 2 - wdDest.height / 2;

	BeginDrawing();

	ClearBackground(BLACK);
	DrawTexturePro(menu.bg, bgSource, bgDest, { 0, 0 }, 0, WHITE);
	DrawTexturePro(menu.window, wdSource, wdDest, { 0, 0 }, 0, WHITE);

	DrawText(menu.title, (int)menu.titlePos.x, (int)menu.titlePos.y, (int)((float)GetScreenWidth() * (5.f / 192.f)), WHITE);
	drawButton(menu.btn[0]);
	drawButton(menu.btn[1]);
	drawButton(menu.btn[2]);
	drawButton(menu.btn[3]);
	drawButton(menu.btn[4]);

	drawCursor(menu.cur);

	EndDrawing();
}

void positionTitle(Menu& menu)
{
	menu.titlePos.x = (float)MeasureText(menu.title, (int)((float)GetScreenWidth() * (5.f / 192.f)));
	menu.titlePos.x = (float)GetScreenWidth() / 2 - menu.titlePos.x / 2;
	menu.titlePos.y = (float)GetScreenHeight() * (9.f / 64.f);
}

void takeInput(Menu& menu, Settings& gSettings)
{
	if (isHovering(menu.cur, menu.btn[3].rec)
		|| isHovering(menu.cur, menu.btn[1].rec)
		|| isHovering(menu.cur, menu.btn[2].rec)
		|| isHovering(menu.cur, menu.btn[4].rec)
		|| isHovering(menu.cur, menu.btn[0].rec))
		menu.cur.state = Cursor::Hover;
	else
		menu.cur.state = Cursor::Idle;

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
	const float btnSpacing = (float)GetScreenHeight() * (1.f / 108.f);

	positionButton(menu.btn[0], ((float)GetScreenHeight() / 8) * 4);
	positionButton(menu.btn[1], (float)GetScreenHeight() - (float)GetScreenHeight() / 8);
	positionButton(menu.btn[2], menu.btn[0].rec.y + menu.btn[0].rec.height + btnSpacing);
	positionButton(menu.btn[3], menu.btn[2].rec.y + menu.btn[2].rec.height + btnSpacing);
	positionButton(menu.btn[4], menu.btn[3].rec.y + menu.btn[3].rec.height + btnSpacing);

	updateButton(menu.btn[0]);
	updateButton(menu.btn[1]);
	updateButton(menu.btn[2]);
	updateButton(menu.btn[3]);
	updateButton(menu.btn[4]);
}

void positionButton(Button& btn, float posY)
{
	btn.rec.y = posY;
	btn.rec.x = ((float)GetScreenWidth() / 4);
}

void controlsMenu(Settings& gSettings, Menu& ui)
{
	const int txtFontSize = (int)((float)GetScreenWidth() * (1.f / 96.f));
	const char* moveTxt[2] = { "Right click anywhere to", "move in that direction" };
	const char* stopTxt[2] = { "Accelerate in opposite", "direction to stop" };
	const char* fireTxt[2] = { "Left click anywhere to", "fire in that direction" };

	int moveTxtSize[2] = { MeasureText(moveTxt[0], txtFontSize), MeasureText(moveTxt[1], txtFontSize) };
	int stopTxtSize[2] = { MeasureText(stopTxt[0], txtFontSize), MeasureText(stopTxt[1], txtFontSize) };
	int fireTxtSize[2] = { MeasureText(fireTxt[0], txtFontSize), MeasureText(fireTxt[1], txtFontSize) };

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

		ui.anim[0] = newAnimation("res/anims/MovementAnim.png", 44, 1);
		ui.anim[1] = newAnimation("res/anims/StopAnim.png", 32, 1);
		ui.anim[2] = newAnimation("res/anims/ShootAnim.png", 6, 3);
	}

	// Update

	controlsMenuUpdate(ui, gSettings);

	// Draw

	Rectangle source{ 0, 0, (float)ui.bg.width, (float)ui.bg.height };
	Rectangle dest{ -((float)GetScreenHeight() * (16.f / 9.f) - (float)GetScreenWidth()) / 2, 0, (float)GetScreenHeight() * (16.f / 9.f), (float)GetScreenHeight() };

	Rectangle wdSource{ 0, 0, (float)ui.window.width, (float)ui.window.height };
	Rectangle wdDest{ 0, 0, (float)GetScreenWidth() * (2.f / 3.f), (float)GetScreenHeight() * (19.f / 20.f) };

	wdDest.x = (float)GetScreenWidth() / 2 - wdDest.width / 2;
	wdDest.y = (float)GetScreenHeight() / 2 - wdDest.height / 2;

	BeginDrawing();
	DrawTexturePro(ui.bg, source, dest, { 0, 0 }, 0, WHITE);
	DrawTexturePro(ui.window, wdSource, wdDest, { 0, 0 }, 0, WHITE);
	DrawText(moveTxt[0], (int)((float)GetScreenWidth() * (1.f / 3.f)) - moveTxtSize[0] / 2,
		(int)((float)GetScreenHeight() * (11.f / 36.f)), txtFontSize, WHITE);
	DrawText(moveTxt[1], (int)((float)GetScreenWidth() * (1.f / 3.f)) - moveTxtSize[1] / 2,
		(int)((float)GetScreenHeight() * (71.f / 216.f)), txtFontSize, WHITE);
	DrawText(stopTxt[0], (int)((float)GetScreenWidth() * (1.f / 3.f)) - stopTxtSize[0] / 2,
		(int)((float)GetScreenHeight() * (7.f / 12.f)), txtFontSize, WHITE);
	DrawText(stopTxt[1], (int)((float)GetScreenWidth() * (1.f / 3.f)) - stopTxtSize[1] / 2,
		(int)((float)GetScreenHeight() * (131.f / 216.f)), txtFontSize, WHITE);
	DrawText(fireTxt[0], (int)((float)GetScreenWidth() * (2.f / 3.f)) - fireTxtSize[0] / 2,
		(int)((float)GetScreenHeight() * (11.f / 36.f)), txtFontSize, WHITE);
	DrawText(fireTxt[1], (int)((float)GetScreenWidth() * (2.f / 3.f)) - fireTxtSize[1] / 2,
		(int)((float)GetScreenHeight() * (71.f / 216.f)), txtFontSize, WHITE);
	drawFrame(ui.anim[0], WHITE);
	drawFrame(ui.anim[1], WHITE);
	drawFrame(ui.anim[2], WHITE);

	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y,
		(int)((float)GetScreenWidth() * (5.f / 192.f)), WHITE);
	drawButton(ui.btn[1]);
	drawCursor(ui.cur);

	EndDrawing();
}

void controlsMenuUpdate(Menu& ui, Settings& gSettings)
{
	positionTitle(ui);
	updateButtons(ui);
	updateCursor(ui.cur);

	for (int i = 0; i < ui.maxAnims; i++)
	{
		updateAnimation(ui.anim[i]);
	}

	setPos(ui.anim[0], { (float)GetScreenWidth() * (1.f / 3.f) - ui.anim[0].dest.width / 2, (float)GetScreenHeight() * (10.f/27.f)});
	setSize(ui.anim[0], { (float)GetScreenWidth() * (5.f/48.f),
		(float)GetScreenWidth()* (5.f / 48.f) });
	ui.anim[0].drawRectangle = true;

	setPos(ui.anim[1], { (float)GetScreenWidth() * (1.f / 3.f) - ui.anim[0].dest.width / 2, (float)GetScreenHeight() * (35.f / 54.f) });
	setSize(ui.anim[1], { (float)GetScreenWidth() * (5.f / 48.f),
		(float)GetScreenWidth()* (5.f / 48.f) });
	ui.anim[1].drawRectangle = true;

	setPos(ui.anim[2], { (float)GetScreenWidth() * (2.f / 3.f) - ui.anim[0].dest.width / 2, (float)GetScreenHeight() * (10.f / 27.f) });
	setSize(ui.anim[2], { (float)GetScreenWidth() * (5.f / 48.f),
		(float)GetScreenWidth()* (5.f / 48.f) });

	if (isHovering(ui.cur, ui.btn[1].rec))
		ui.cur.state = Cursor::Hover;
	else
		ui.cur.state = Cursor::Idle;

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
	updateCursor(ui.cur);

	for (int i = 0; i < ui.chkBxQty; i++)
	{
		ui.chbxs[i].rec.x = (float)GetScreenWidth() / 4;
		ui.chbxs[i].rec.y = ((float)GetScreenHeight() * (35.f/108.f) + (float)i * ((float)GetScreenHeight() * (5.f/54.f)));
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

	if (isHovering(ui.cur, ui.chbxs[1].rec)
		|| isHovering(ui.cur, ui.chbxs[2].rec)
		|| isHovering(ui.cur, ui.chbxs[0].rec)
		|| isHovering(ui.cur, ui.btn[1].rec))
		ui.cur.state = Cursor::Hover;
	else
		ui.cur.state = Cursor::Idle;


	// Draw
	Rectangle source{ 0, 0, (float)ui.bg.width, (float)ui.bg.height };
	Rectangle dest{ -((float)GetScreenHeight() * (16.f / 9.f) - (float)GetScreenWidth()) / 2, 0, (float)GetScreenHeight() * (16.f / 9.f), (float)GetScreenHeight() };

	Rectangle wdSource{ 0, 0, (float)ui.window.width, (float)ui.window.height };
	Rectangle wdDest{ 0, 0, (float)GetScreenWidth() * (2.f / 3.f), (float)GetScreenHeight() * (19.f / 20.f) };

	wdDest.x = (float)GetScreenWidth() / 2 - wdDest.width / 2;
	wdDest.y = (float)GetScreenHeight() / 2 - wdDest.height / 2;

	BeginDrawing();
	DrawTexturePro(ui.bg, source, dest, { 0, 0 }, 0, WHITE);
	DrawTexturePro(ui.window, wdSource, wdDest, { 0, 0 }, 0, WHITE);

	drawButton(ui.btn[1]);
	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y,
		(int)((float)GetScreenWidth() * (5.f / 192.f)), WHITE);
	for (int i = 0; i < ui.chkBxQty; i++)
	{
		drawCheckbox(ui.chbxs[i]);
	}
	drawCursor(ui.cur);

	EndDrawing();
}

void creditsMenu(Settings& gSettings, Menu& ui)
{
	const char* credits[] = { "Programing:", "Topo - Mateo Fabbri","", "Art:", "Chiara Colombo",
		"CraftPix", "(https://craftpix.net/product/asteroids-crusher-2d-game-kit/)" };
	const Color color[] = { WHITE, WHITE, BLACK, RED, RED, RED, RED };
	int posY = GetScreenHeight() / 2 - 50 * 3;

	if (!ui.isActive)
	{
		TakeScreenshot("PauseScreen.png");
		ui.bg = LoadTextureFromImage(LoadImage("PauseScreen.png"));
		ui.title = "Credits";
		ui.isActive = true;
		ui.btn[1].text = "Back";
		ui.bg = LoadTexture("res/bgs/backgroundMenu.png");
		ui.window = LoadTexture("res/ui/Window.png");
	}

	// Update
	positionTitle(ui);
	updateButtons(ui);
	updateCursor(ui.cur);

	if (isButtonPressed(ui.btn[1]))
	{
		gSettings.scene = Scene::MainMenu;
		ui.isActive = false;
	}
	if (isHovering(ui.cur, ui.btn[1].rec))
		ui.cur.state = Cursor::Hover;
	else
		ui.cur.state = Cursor::Idle;

	// Draw

	Rectangle source{ 0, 0, (float)ui.bg.width, (float)ui.bg.height };
	Rectangle dest{ -((float)GetScreenHeight() * (16.f / 9.f) - (float)GetScreenWidth()) / 2, 0, (float)GetScreenHeight() * (16.f / 9.f), (float)GetScreenHeight() };

	Rectangle wdSource{ 0, 0, (float)ui.window.width, (float)ui.window.height };
	Rectangle wdDest{ 0, 0, (float)GetScreenWidth() * (2.f / 3.f), (float)GetScreenHeight() * (19.f / 20.f) };

	wdDest.x = (float)GetScreenWidth() / 2 - wdDest.width / 2;
	wdDest.y = (float)GetScreenHeight() / 2 - wdDest.height / 2;

	BeginDrawing();

	ClearBackground(BLACK);

	DrawTexturePro(ui.bg, source, dest, { 0, 0 }, 0, WHITE);
	DrawTexturePro(ui.window, wdSource, wdDest, { 0, 0 }, 0, WHITE);

	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y,
		(int)((float)GetScreenWidth() * (5.f / 192.f)), WHITE);
	drawButton(ui.btn[1]);

	for (int i = 0; i < 7; i++)
	{
		const int fontSize = (int)((float)GetScreenWidth() * ( i >= 6 ? (1.f / 96.f) : (5.f / 192.f)));

		DrawText(credits[i], GetScreenWidth() / 2 - MeasureText(credits[i], fontSize) / 2,
			posY, fontSize, color[i]);
		posY += 50;
	}
	drawCursor(ui.cur);

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
	updateCursor(ui.cur);

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

	if (isHovering(ui.cur, ui.btn[0].rec)
		|| isHovering(ui.cur, ui.btn[1].rec))
		ui.cur.state = Cursor::Hover;
	else
		ui.cur.state = Cursor::Idle;

	// Draw
	Rectangle wdSource{ 0, 0, (float)ui.window.width, (float)ui.window.height };
	Rectangle wdDest{ 0, 0, (float)GetScreenWidth() * (2.f / 3.f), (float)GetScreenHeight() * (19.f / 20.f) };

	wdDest.x = (float)GetScreenWidth() / 2 - wdDest.width / 2;
	wdDest.y = (float)GetScreenHeight() / 2 - wdDest.height / 2;

	BeginDrawing();

	ClearBackground(BLACK);
	DrawTexture(ui.bg, 0, 0, WHITE);
	DrawTexturePro(ui.window, wdSource, wdDest, { 0, 0 }, 0, WHITE);

	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, (int)((float)GetScreenWidth() * (5.f / 192.f)), WHITE);
	drawButton(ui.btn[0]);
	drawButton(ui.btn[1]);
	drawCursor(ui.cur);

	EndDrawing();
}