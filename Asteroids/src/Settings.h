#pragma once

enum class Scene
{
	Exit,
	Game,
	MainMenu,
	SettingsMenu,
	ControlsMenu,
	Credits,
	Pause
};

struct Settings
{
	Scene scene;
	bool drawFps;
	bool inverseSpawn;
	bool showColiders;
};

Settings newSettings();