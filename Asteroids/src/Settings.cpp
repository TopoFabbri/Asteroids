#include "Settings.h"

Settings newSettings()
{
	Settings set{};

	set.drawFps = false;
	set.scene = Scene::MainMenu;
	set.circleWarp = false;

	return set;
}