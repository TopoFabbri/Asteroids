#include "Settings.h"

Settings newSettings()
{
	Settings set{};

	set.drawFps = false;
	set.scene = Scene::MainMenu;
	set.inverseSpawn = false;
	set.showColiders = false;

	return set;
}