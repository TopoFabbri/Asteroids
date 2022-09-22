#include "Settings.h"

Settings newSettings()
{
	Settings set{};

	set.drawFps = false;
	set.scene = Scene::MainMenu;

	return set;
}