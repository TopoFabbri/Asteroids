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
	bool circleWarp;
	bool showColliders;
};

Settings newSettings();